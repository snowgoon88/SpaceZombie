/* zscpipe.c : try to inflate (using zlib) some file from SC
   Based on zpipe.c by Mark Adlet and some hints from
   http://www.unknowncheats.me/forum/other-games/107917-star-conflict-3d-model-file-format.html
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "zlib.h"

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#define CHUNK 16384

/*   /\* declare a file pointer *\/ */
/* FILE    *infile; */
/* char    *buffer; */
/* long    numbytes; */
 
/* /\* open an existing file for reading *\/ */
/* infile = fopen("test.rib", "r"); */
 
/* /\* quit if the file does not exist *\/ */
/* if(infile == NULL) */
/*     return 1; */
/* free the memory we used for the buffer */
/* free(buffer); */


/**
 * Read an entire stream into memory.
 */
int read_file( FILE *src, unsigned char **buffer)
{
 
  /* Get the number of bytes */
  fseek(src, 0L, SEEK_END);
  long numbytes = ftell(src);
  fprintf( stderr, "read %ld char\n", numbytes );
 
  /* reset the file position indicator to 
     the beginning of the file */
  fseek(src, 0L, SEEK_SET);	
 
  /* grab sufficient memory for the 
     buffer to hold the text */
  *buffer = (unsigned char*)calloc(numbytes, sizeof(unsigned char));	
 
  /* memory error */
  if(*buffer == NULL)
    return -1;
 
  /* copy all the text into the buffer */
  fread(*buffer, sizeof(unsigned char), numbytes, src);
  fclose(src);
 
  /* confirm we have read the file by
     outputing it to the console */
  //printf("The stream contains this text\n\n%s", *buffer);
  return numbytes;
 }


int uncompress_nohdr(Bytef *dest, uLongf *destLen,
		     const Bytef *source, uLong sourceLen)
{
  // next_in,  avail_in, total_in, next_out, avail_out, ...
  z_stream stream = { (Bytef*)(source+4), (uInt)sourceLen-8, 0,
		      dest, (uInt)*destLen, NULL };
  
  int err = inflateInit2(&stream, -15);		//negative means skip header
  if (err != Z_OK) {
    fprintf( stderr, "ERROR in inflateInit2 %d\n", err);
    return err;
  }
  
  if( Z_STREAM_END == (err = inflate(&stream, Z_FINISH)) ) {
    *destLen = stream.total_out;
    return inflateEnd(&stream);
  }
  inflateEnd(&stream);
  return (err == Z_NEED_DICT || (err == Z_BUF_ERROR && stream.avail_in == 0)) ? Z_DATA_ERROR : err;
}

/* Decompress from file source to file dest until stream ends or EOF.
   inf() returns Z_OK on success, Z_MEM_ERROR if memory could not be
   allocated for processing, Z_DATA_ERROR if the deflate data is
   invalid or incomplete, Z_VERSION_ERROR if the version of zlib.h and
   the version of the library linked do not match, or Z_ERRNO if there
   is an error reading or writing the files. */
int inf(FILE *source, FILE *dest)
{
    int ret;
    unsigned have;
    z_stream strm;
    unsigned char in[CHUNK];
    unsigned char out[CHUNK];

    /* allocate inflate state */
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit2(&strm, -15); //negative means skip header
    if (ret != Z_OK) {
      fputs("should initialize strm before calling inflateInit2", stderr);
      return ret;
    }
    
    /* decompress until deflate stream ends or end of file */
    int fcount = 0;
    int icount = 0;
    do {
      fcount += 1;
      fprintf( stderr, "*********************** fcount=%d : ", fcount);

      strm.avail_in = fread(in, 1, CHUNK, source);
      if (ferror(source)) {
	(void)inflateEnd(&strm);
	return Z_ERRNO;
      }
      if (strm.avail_in == 0)
	break;
      strm.next_in = in;
      
      /* run inflate() on input until output buffer not full */
      
      icount = 0;
      do {
	icount += 1;
	fprintf( stderr, ">>>>>>>>>>>> icount=%d : ", icount);

	strm.avail_out = CHUNK;
	strm.next_out = out;
	ret = inflate(&strm, Z_NO_FLUSH);
	assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
	switch (ret) {
	case Z_NEED_DICT:
	  ret = Z_DATA_ERROR;     /* and fall through */
	case Z_DATA_ERROR:
	case Z_MEM_ERROR:
	  (void)inflateEnd(&strm);
	  return ret;
	}
	have = CHUNK - strm.avail_out;
	if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
	  (void)inflateEnd(&strm);
	  return Z_ERRNO;
	}
      } while (strm.avail_out == 0);
      /* done when inflate() says it's done */
    } while (ret != Z_STREAM_END);
    
    /* clean up and return */
    (void)inflateEnd(&strm);
    return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}
    
/* report a zlib or i/o error */
void zerr(int ret)
{
    fputs("zscpipe: ", stderr);
    switch (ret) {
    case Z_ERRNO:
        if (ferror(stdin))
            fputs("error reading stdin\n", stderr);
        if (ferror(stdout))
            fputs("error writing stdout\n", stderr);
        break;
    case Z_STREAM_ERROR:
        fputs("invalid compression level\n", stderr);
        break;
    case Z_DATA_ERROR:
        fputs("invalid or incomplete deflate data\n", stderr);
        break;
    case Z_MEM_ERROR:
        fputs("out of memory\n", stderr);
        break;
    case Z_VERSION_ERROR:
        fputs("zlib version mismatch!\n", stderr);
	break;
    default:
	fputs(zError(ret), stderr);
        fputs(" - unknown ZERROE\n", stderr);
    }
}

/**
 * decompress from stdin to stdout
 */
int main(int argc, char **argv)
{
  int ret;
  
  /* avoid end-of-line conversions */
  SET_BINARY_MODE(stdin);
  SET_BINARY_MODE(stdout);

  /* do decompression if no argument */
  if (argc == 1) {
    ret = inf(stdin, stdout);
    if (ret != Z_OK)
      zerr(ret);
    return ret;
  }
  /* do read_file if -r specified */
  else if (argc == 2 && strcmp(argv[1], "-r") == 0) {
    unsigned char *buffer;
    ret = read_file( stdin, &buffer );
    fprintf( stderr, "read %d char\n",ret);
    if (ret < 0) {
      fprintf( stderr, "error while reading stream\n");
      return ret;
    }

    /* try to inflate without the first 2 bytes */
    uLongf out_len;
    unsigned char *buf_out = (unsigned char*)calloc(10000, sizeof(char));
    ret = uncompress_nohdr( buf_out, &out_len, (Bytef*) buffer, ret);
    if (ret != Z_OK) 
      zerr(ret);
    printf("Z_OK is %d, ret=%d\n", Z_OK,ret);
    printf("out_len = %ld\n",out_len);
    printf("Inflated = %s\n", buf_out);
    return ret;
  }
  
  /* otherwise, report usage */
  else {
    fputs("zscpipe usage: zpipe < source > dest\n", stderr);
    return 1;
  }
}
