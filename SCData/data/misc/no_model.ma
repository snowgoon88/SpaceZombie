//Maya ASCII 2008 scene
//Name: no_model.ma
//Last modified: Fri, Jan 14, 2011 04:14:56 PM
//Codeset: 1251
requires maya "2008";
requires "COLLADA" "3.05B.T03";
requires "MapTools" "8.0";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya Unlimited 2008";
fileInfo "version" "2008 Extension 2";
fileInfo "cutIdentifier" "200802250025-718075";
fileInfo "osv" "Microsoft Windows XP Service Pack 3 (Build 2600)\n";
createNode transform -s -n "persp";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 4.967556472345044 5.3235024365927117 -3.5302586319063467 ;
	setAttr ".r" -type "double3" -41.138352729599326 125.39999999999614 0 ;
createNode camera -s -n "perspShape" -p "persp";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 8.0919108686696752;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 100.1 0 ;
	setAttr ".r" -type "double3" -89.999999999999986 0 0 ;
createNode camera -s -n "topShape" -p "top";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 100.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "top";
	setAttr ".den" -type "string" "top_depth";
	setAttr ".man" -type "string" "top_mask";
	setAttr ".hc" -type "string" "viewSet -t %camera";
	setAttr ".o" yes;
createNode transform -s -n "front";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 0 100.1 ;
createNode camera -s -n "frontShape" -p "front";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 100.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
createNode transform -s -n "side";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 100.1 0 0 ;
	setAttr ".r" -type "double3" 0 89.999999999999986 0 ;
createNode camera -s -n "sideShape" -p "side";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 100.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
createNode transform -n "pCube1";
	addAttr -ci true -sn "dae" -ln "collada" -dt "string";
	setAttr ".s" -type "double3" 0.5 0.5 0.5 ;
createNode mesh -n "pCubeShape1" -p "pCube1";
	addAttr -ci true -sn "dae" -ln "collada" -dt "string";
	addAttr -ci true -sn "mso" -ln "miShadingSamplesOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "msh" -ln "miShadingSamples" -min 0 -max 12 -smx 8 -at "float";
	addAttr -ci true -sn "mdo" -ln "miMaxDisplaceOverride" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "mmd" -ln "miMaxDisplace" -min 0 -smx 1 -at "float";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovc" 6;
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr -s 14 ".uvst[0].uvsp[0:13]" -type "float2" 0 0 1 0 0 1 1 1 
		0 2 1 2 0 3 1 3 0 4 1 4 2 0 2 1 -1 0 -1 1;
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr -s 8 ".vt[0:7]"  -1 -1 1 1 -1 1 -1 1 1 1 1 1 -1 1 -1 1 1 
		-1 -1 -1 -1 1 -1 -1;
	setAttr -s 18 ".ed[0:17]"  0 1 0 1 2 1 
		2 0 0 1 3 0 3 2 0 3 4 1 
		4 2 0 3 5 0 5 4 0 5 6 1 
		6 4 0 5 7 0 7 6 0 7 0 1 
		0 6 0 7 1 0 7 3 1 0 4 1;
	setAttr -s 12 ".fc[0:11]" -type "polyFaces" 
		f 3 0 1 2 
		mu 0 3 0 1 2 
		f 3 3 4 -2 
		mu 0 3 1 3 2 
		f 3 -5 5 6 
		mu 0 3 2 3 4 
		f 3 7 8 -6 
		mu 0 3 3 5 4 
		f 3 -9 9 10 
		mu 0 3 4 5 6 
		f 3 11 12 -10 
		mu 0 3 5 7 6 
		f 3 -13 13 14 
		mu 0 3 6 7 8 
		f 3 15 -1 -14 
		mu 0 3 7 9 8 
		f 3 -16 16 -4 
		mu 0 3 1 10 3 
		f 3 -12 -8 -17 
		mu 0 3 10 11 3 
		f 3 -15 17 -11 
		mu 0 3 12 0 13 
		f 3 -3 -7 -18 
		mu 0 3 0 2 13 ;
	setAttr ".cd" -type "dataPolyComponent" Index_Data Edge 0 ;
	setAttr ".cvd" -type "dataPolyComponent" Index_Data Vertex 0 ;
createNode transform -n "collision1";
	addAttr -ci true -sn "shapeType" -ln "shapeType" -dv 1 -at "long";
	addAttr -ci true -sn "boxScale" -ln "boxScale" -at "float3" -nc 3;
	addAttr -ci true -sn "boxScaleX" -ln "boxScaleX" -at "float" -p "boxScale";
	addAttr -ci true -sn "boxScaleY" -ln "boxScaleY" -at "float" -p "boxScale";
	addAttr -ci true -sn "boxScaleZ" -ln "boxScaleZ" -at "float" -p "boxScale";
	addAttr -ci true -sn "point1" -ln "point1" -at "float3" -nc 3;
	addAttr -ci true -sn "point1X" -ln "point1X" -at "float" -p "point1";
	addAttr -ci true -sn "point1Y" -ln "point1Y" -at "float" -p "point1";
	addAttr -ci true -sn "point1Z" -ln "point1Z" -at "float" -p "point1";
	addAttr -ci true -sn "point2" -ln "point2" -at "float3" -nc 3;
	addAttr -ci true -sn "point2X" -ln "point2X" -at "float" -p "point2";
	addAttr -ci true -sn "point2Y" -ln "point2Y" -at "float" -p "point2";
	addAttr -ci true -sn "point2Z" -ln "point2Z" -at "float" -p "point2";
	addAttr -ci true -sn "radius" -ln "radius" -dv 1 -at "double";
	setAttr -l on ".s";
	setAttr -l on ".sh";
createNode collisionShape -n "collisionShape1" -p "collision1";
	setAttr -k off ".v";
	setAttr ".ove" yes;
	setAttr ".ovc" 6;
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr ".st" 1;
createNode transform -n "Model_Attribute";
	addAttr -ci true -sn "Mesh" -ln "Mesh" -bt "UNKN" -dv 1 -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "PD" -ln "Physics" -bt "UNKN" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "SV" -ln "Scale" -bt "UNKN" -at "float3" -nc 3;
	addAttr -ci true -sn "SV0" -ln "Scale0" -bt "UNKN" -dv 1 -at "float" -p "Scale";
	addAttr -ci true -sn "SV1" -ln "Scale1" -bt "UNKN" -dv 1 -at "float" -p "Scale";
	addAttr -ci true -sn "SV2" -ln "Scale2" -bt "UNKN" -dv 1 -at "float" -p "Scale";
	addAttr -ci true -sn "BN" -ln "InfluenceBonesNumber" -bt "UNKN" -min 0 -max 4 -at "long";
	addAttr -ci true -sn "OP" -ln "OutputPath" -bt "UNKN" -dt "string";
	addAttr -ci true -sn "DOP" -ln "DaeOutputPath" -bt "UNKN" -dt "string";
	addAttr -ci true -sn "DlcOP" -ln "DlcOutputPath" -bt "UNKN" -dt "string";
	addAttr -ci true -sn "REM" -ln "ReferenceModel" -bt "UNKN" -dt "string";
	addAttr -ci true -sn "BTOR" -ln "BonesToRemove" -bt "UNKN" -dt "string";
	addAttr -ci true -sn "EXTBNS" -ln "ExtendingBones" -bt "UNKN" -dt "string";
	addAttr -ci true -sn "NA" -ln "NumAnimations" -bt "UNKN" -at "long";
	addAttr -ci true -sn "AA" -ln "AbsoluteAnimations" -bt "UNKN" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "DA" -ln "DefaultAnimation" -bt "UNKN" -at "long";
	addAttr -ci true -sn "NOTT" -ln "NotTriangulate" -bt "UNKN" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "GM" -ln "GrassModel" -bt "UNKN" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "PM" -ln "ParticleMesh" -bt "UNKN" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "PBM" -ln "BloodParticleMesh" -bt "UNKN" -min 0 -max 1 -at "bool";
	setAttr ".OP" -type "string" "models/misc/no_model";
	setAttr ".DOP" -type "string" "";
	setAttr ".DlcOP" -type "string" "";
	setAttr ".REM" -type "string" "";
	setAttr ".BTOR" -type "string" "";
	setAttr ".EXTBNS" -type "string" "";
	setAttr -l on ".NA";
createNode lightLinker -n "lightLinker1";
	setAttr -s 5 ".lnk";
	setAttr -s 5 ".slnk";
createNode displayLayerManager -n "layerManager";
createNode displayLayer -n "defaultLayer";
createNode renderLayerManager -n "renderLayerManager";
	setAttr -s 2 ".rlmi[1]"  1;
	setAttr -s 2 ".rlmi";
createNode renderLayer -n "defaultRenderLayer";
	setAttr ".g" yes;
	setAttr ".rndr" no;
createNode colladaDocument -n "colladaDocuments";
	setAttr -s 2 ".doc";
	setAttr ".doc[0].fn" -type "string" "D:/_Proj/dancewar_source/data/models/misc/no_model.dae";
	setAttr -s 6 ".doc[0].e";
	setAttr ".doc[0].e[0]" -type "string" "colladafxShader1";
	setAttr ".doc[0].e[1]" -type "string" "pCubeShape1-lib";
	setAttr ".doc[0].e[2]" -type "string" "pCube1";
	setAttr ".doc[0].e[3]" -type "string" "nxRigidBody12";
	setAttr ".doc[0].e[4]" -type "string" "Model_Attribute";
	setAttr ".doc[0].e[5]" -type "string" "physics1";
	setAttr ".doc[1].fn" -type "string" "";
createNode file -n "file1";
	setAttr ".ftn" -type "string" "Y:/art/source//textures/misc/no_model.dds";
createNode place2dTexture -n "place2dTexture1";
createNode colladafxShader -n "colladafxShader2";
	addAttr -ci true -sn "texDiffuse" -ln "texDiffuse" -bt "UNKN" -dt "string";
	addAttr -ci true -sn "texDiffuse2" -ln "texDiffuse2" -bt "UNKN" -dt "string";
	addAttr -ci true -sn "texLightmap" -ln "texLightmap" -bt "UNKN" -dt "string";
	addAttr -ci true -sn "texNormal" -ln "texNormal" -bt "UNKN" -dt "string";
	addAttr -ci true -sn "texDetail" -ln "texDetail" -bt "UNKN" -dt "string";
	addAttr -ci true -sn "envMap" -ln "envMap" -bt "UNKN" -dt "string";
	addAttr -ci true -sn "texAmbOcclusion" -ln "texAmbOcclusion" -bt "UNKN" -dt "string";
	addAttr -ci true -sn "texSpecular" -ln "texSpecular" -bt "UNKN" -dt "string";
	addAttr -ci true -sn "TotalMatrix" -ln "TotalMatrix" -bt "UNKN" -dt "matrix";
	addAttr -ci true -sn "WorldMatrix" -ln "WorldMatrix" -bt "UNKN" -dt "matrix";
	addAttr -ci true -sn "ViewMatrixInv" -ln "ViewMatrixInv" -bt "UNKN" -dt "matrix";
	addAttr -ci true -uac -sn "DiffuseSampler" -ln "DiffuseSampler" -bt "UNKN" -at "float3" 
		-nc 3;
	addAttr -ci true -sn "DiffuseSamplerr" -ln "DiffuseSamplerR" -bt "UNKN" -dv 0.5 
		-at "float" -p "DiffuseSampler";
	addAttr -ci true -sn "DiffuseSamplerg" -ln "DiffuseSamplerG" -bt "UNKN" -dv 0.5 
		-at "float" -p "DiffuseSampler";
	addAttr -ci true -sn "DiffuseSamplerb" -ln "DiffuseSamplerB" -bt "UNKN" -dv 0.5 
		-at "float" -p "DiffuseSampler";
	addAttr -ci true -uac -sn "Diffuse2Sampler" -ln "Diffuse2Sampler" -bt "UNKN" -at "float3" 
		-nc 3;
	addAttr -ci true -sn "Diffuse2Samplerr" -ln "Diffuse2SamplerR" -bt "UNKN" -dv 0.5 
		-at "float" -p "Diffuse2Sampler";
	addAttr -ci true -sn "Diffuse2Samplerg" -ln "Diffuse2SamplerG" -bt "UNKN" -dv 0.5 
		-at "float" -p "Diffuse2Sampler";
	addAttr -ci true -sn "Diffuse2Samplerb" -ln "Diffuse2SamplerB" -bt "UNKN" -dv 0.5 
		-at "float" -p "Diffuse2Sampler";
	addAttr -ci true -uac -k true -sn "LightDir" -ln "LightDir" -bt "UNKN" -at "float3" 
		-nc 3;
	addAttr -ci true -k true -sn "LightDirr" -ln "LightDirR" -bt "UNKN" -at "float" 
		-p "LightDir";
	addAttr -ci true -k true -sn "LightDirg" -ln "LightDirG" -bt "UNKN" -dv 1 -at "float" 
		-p "LightDir";
	addAttr -ci true -k true -sn "LightDirb" -ln "LightDirB" -bt "UNKN" -at "float" 
		-p "LightDir";
	addAttr -ci true -uac -k true -sn "AmbientColor" -ln "AmbientColor" -bt "UNKN" -at "float3" 
		-nc 3;
	addAttr -ci true -k true -sn "AmbientColorr" -ln "AmbientColorR" -bt "UNKN" -dv 
		0.20000000298023224 -at "float" -p "AmbientColor";
	addAttr -ci true -k true -sn "AmbientColorg" -ln "AmbientColorG" -bt "UNKN" -dv 
		0.20000000298023224 -at "float" -p "AmbientColor";
	addAttr -ci true -k true -sn "AmbientColorb" -ln "AmbientColorB" -bt "UNKN" -dv 
		0.20000000298023224 -at "float" -p "AmbientColor";
	addAttr -ci true -uac -k true -sn "DiffuseColor" -ln "DiffuseColor" -bt "UNKN" -at "float3" 
		-nc 3;
	addAttr -ci true -k true -sn "DiffuseColorr" -ln "DiffuseColorR" -bt "UNKN" -dv 
		1 -at "float" -p "DiffuseColor";
	addAttr -ci true -k true -sn "DiffuseColorg" -ln "DiffuseColorG" -bt "UNKN" -dv 
		1 -at "float" -p "DiffuseColor";
	addAttr -ci true -k true -sn "DiffuseColorb" -ln "DiffuseColorB" -bt "UNKN" -dv 
		1 -at "float" -p "DiffuseColor";
	addAttr -ci true -sn "Invisible" -ln "Invisible" -bt "UNKN" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "User0" -ln "User0" -bt "UNKN" -min 0 -max 1 -at "bool";
	addAttr -ci true -sn "AmbientColor_Table" -ln "AmbientColor_Table" -dt "string";
	addAttr -ci true -sn "DiffuseColor_Table" -ln "DiffuseColor_Table" -dt "string";
	addAttr -ci true -sn "LightDir_Table" -ln "LightDir_Table" -dt "string";
	setAttr ".vpar" -type "stringArray" 0  ;
	setAttr ".upar" -type "stringArray" 0  ;
	setAttr ".vp" -type "string" "Y:/evil-shaders/dynamics/Dynamic_Diffuse.cgfx";
	setAttr ".vpe" -type "string" "VertexProgram";
	setAttr ".fp" -type "string" "Y:/evil-shaders/dynamics/Dynamic_Diffuse.cgfx";
	setAttr ".fpe" -type "string" "FragmentProgram";
	setAttr ".c0" -type "string" "";
	setAttr ".t0" -type "string" "map1";
	setAttr ".t1" -type "string" "tangent";
	setAttr ".t2" -type "string" "binormal";
	setAttr ".t3" -type "string" "";
	setAttr ".t4" -type "string" "";
	setAttr ".t5" -type "string" "";
	setAttr ".t6" -type "string" "";
	setAttr ".t7" -type "string" "";
	setAttr ".rs" -type "stringArray" 0  ;
	setAttr ".drs" -type "string" "";
	setAttr ".Diffuse2Sampler" -type "float3" 0 0 0 ;
createNode shadingEngine -n "colladafxPasses1SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo1";
createNode objectSet -n "VisualScene";
	addAttr -ci true -sn "GlobalColor" -ln "GlobalColor" -dv 1 -at "long";
	addAttr -ci true -sn "CurrentSet" -ln "CurrentSet" -dt "string";
	setAttr ".ihi" 0;
	setAttr -s 2 ".dnsm";
	setAttr ".an" -type "string" "gCharacterSet";
	setAttr ".GlobalColor" 17;
	setAttr ".CurrentSet" -type "string" "no_model";
createNode shadingEngine -n "colladafxShader2SG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo2";
createNode script -n "uiConfigurationScriptNode";
	setAttr ".b" -type "string" (
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"top\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n"
		+ "                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"base_OpenGL_Renderer\" \n                -colorResolution 256 256 \n"
		+ "                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n"
		+ "                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"top\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n"
		+ "            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"base_OpenGL_Renderer\" \n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n"
		+ "            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n"
		+ "\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"side\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n"
		+ "                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"base_OpenGL_Renderer\" \n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n"
		+ "                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"side\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n"
		+ "            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"base_OpenGL_Renderer\" \n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 1\n"
		+ "            -deformers 1\n            -dynamics 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"front\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n"
		+ "                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"base_OpenGL_Renderer\" \n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n"
		+ "                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n"
		+ "                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n"
		+ "            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n            -rendererName \"base_OpenGL_Renderer\" \n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n"
		+ "            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `modelPanel -unParent -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            modelEditor -e \n                -camera \"persp\" \n                -useInteractiveMode 0\n                -displayLights \"default\" \n                -displayAppearance \"wireframe\" \n                -activeOnly 0\n                -wireframeOnShaded 0\n                -headsUpDisplay 1\n                -selectionHiliteDisplay 1\n                -useDefaultMaterial 0\n                -bufferMode \"double\" \n                -twoSidedLighting 1\n                -backfaceCulling 0\n                -xray 0\n                -jointXray 0\n                -activeComponentsXray 0\n                -displayTextures 0\n                -smoothWireframe 0\n                -lineWidth 1\n                -textureAnisotropic 0\n                -textureHilight 1\n"
		+ "                -textureSampling 2\n                -textureDisplay \"modulate\" \n                -textureMaxSize 16384\n                -fogging 0\n                -fogSource \"fragment\" \n                -fogMode \"linear\" \n                -fogStart 0\n                -fogEnd 100\n                -fogDensity 0.1\n                -fogColor 0.5 0.5 0.5 1 \n                -maxConstantTransparency 1\n                -rendererName \"base_OpenGL_Renderer\" \n                -colorResolution 256 256 \n                -bumpResolution 512 512 \n                -textureCompression 0\n                -transparencyAlgorithm \"frontAndBackCull\" \n                -transpInShadows 0\n                -cullingOverride \"none\" \n                -lowQualityLighting 0\n                -maximumNumHardwareLights 1\n                -occlusionCulling 0\n                -shadingModel 0\n                -useBaseRenderer 0\n                -useReducedRenderer 0\n                -smallObjectCulling 0\n                -smallObjectThreshold -1 \n                -interactiveDisableShadows 0\n"
		+ "                -interactiveBackFaceCull 0\n                -sortTransparent 1\n                -nurbsCurves 1\n                -nurbsSurfaces 1\n                -polymeshes 1\n                -subdivSurfaces 1\n                -planes 1\n                -lights 1\n                -cameras 1\n                -controlVertices 1\n                -hulls 1\n                -grid 1\n                -joints 1\n                -ikHandles 1\n                -deformers 1\n                -dynamics 1\n                -fluids 1\n                -hairSystems 1\n                -follicles 1\n                -nCloths 1\n                -nRigids 1\n                -dynamicConstraints 1\n                -locators 1\n                -manipulators 1\n                -dimensions 1\n                -handles 1\n                -pivots 1\n                -textures 1\n                -strokes 1\n                -shadows 0\n                $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 1\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -maxConstantTransparency 1\n"
		+ "            -rendererName \"base_OpenGL_Renderer\" \n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -fluids 1\n"
		+ "            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -shadows 0\n            $editorName;\nmodelEditor -e -viewSelected 0 $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"Outliner\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `outlinerPanel -unParent -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels `;\n\t\t\t$editorName = $panelName;\n            outlinerEditor -e \n                -showShapes 0\n                -showAttributes 0\n                -showConnected 0\n                -showAnimCurvesOnly 0\n                -showMuteInfo 0\n                -autoExpand 0\n                -showDagOnly 1\n                -ignoreDagHierarchy 0\n"
		+ "                -expandConnections 0\n                -showUnitlessCurves 1\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 0\n                -highlightActive 1\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"defaultSetFilter\" \n                -showSetMembers 1\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n"
		+ "\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -showShapes 0\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -autoExpand 0\n            -showDagOnly 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -editAttrName 0\n"
		+ "            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"graphEditor\" (localizedPanelLabel(\"Graph Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"graphEditor\" -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -autoExpand 1\n                -showDagOnly 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n"
		+ "                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n"
		+ "                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -autoExpand 1\n                -showDagOnly 0\n                -ignoreDagHierarchy 0\n"
		+ "                -expandConnections 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n"
		+ "            animCurveEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 1\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showResults \"off\" \n                -showBufferCurves \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dopeSheetPanel\" (localizedPanelLabel(\"Dope Sheet\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dopeSheetPanel\" -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n"
		+ "                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -autoExpand 0\n                -showDagOnly 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n"
		+ "                -attrAlphaOrder \"default\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n"
		+ "                -showShapes 1\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -autoExpand 0\n                -showDagOnly 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n"
		+ "                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayKeys 1\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"clipEditorPanel\" -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayKeys 0\n                -displayTangents 0\n                -displayActiveKeys 0\n                -displayActiveKeyTangents 0\n                -displayInfinities 0\n                -autoFit 0\n                -snapTime \"none\" \n"
		+ "                -snapValue \"none\" \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph Hierarchy\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperGraphPanel\" -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -zoom 1\n                -animateTransition 0\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n"
		+ "                -graphType \"DAG\" \n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -zoom 1\n                -animateTransition 0\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n"
		+ "                -graphType \"DAG\" \n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperShadePanel\" (localizedPanelLabel(\"Hypershade\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"hyperShadePanel\" -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\tif ($useSceneConfig) {\n\t\tscriptedPanel -e -to $panelName;\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"visorPanel\" (localizedPanelLabel(\"Visor\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"visorPanel\" -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Texture Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"polyTexturePlacementPanel\" -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Texture Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"multiListerPanel\" (localizedPanelLabel(\"Multilister\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"multiListerPanel\" -l (localizedPanelLabel(\"Multilister\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Multilister\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"renderWindowPanel\" -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"blendShapePanel\" (localizedPanelLabel(\"Blend Shape\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\tblendShapePanel -unParent -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels ;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tblendShapePanel -edit -l (localizedPanelLabel(\"Blend Shape\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynRelEdPanel\" -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"devicePanel\" (localizedPanelLabel(\"Devices\")) `;\n\tif (\"\" == $panelName) {\n"
		+ "\t\tif ($useSceneConfig) {\n\t\t\tdevicePanel -unParent -l (localizedPanelLabel(\"Devices\")) -mbv $menusOkayInPanels ;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tdevicePanel -edit -l (localizedPanelLabel(\"Devices\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"relationshipPanel\" -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n\tif (\"\" == $panelName) {\n"
		+ "\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"referenceEditorPanel\" -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"componentEditorPanel\" (localizedPanelLabel(\"Component Editor\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"componentEditorPanel\" -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Component Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"dynPaintScriptedPanelType\" -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"webBrowserPanel\" (localizedPanelLabel(\"Web Browser\")) `;\n\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"webBrowserPanel\" -l (localizedPanelLabel(\"Web Browser\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Web Browser\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n"
		+ "\tif (\"\" == $panelName) {\n\t\tif ($useSceneConfig) {\n\t\t\t$panelName = `scriptedPanel -unParent  -type \"scriptEditorPanel\" -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels `;\n\t\t}\n\t} else {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\tif ($useSceneConfig) {\n\t\tscriptedPanel -e -to $panelName;\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-defaultImage \"\"\n\t\t\t\t-image \"\"\n\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"vertical2\\\" -ps 1 20 100 -ps 2 80 100 $gMainPane;\"\n\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Outliner\")) \n\t\t\t\t\t\"outlinerPanel\"\n\t\t\t\t\t\"$panelName = `outlinerPanel -unParent -l (localizedPanelLabel(\\\"Outliner\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\noutlinerEditor -e \\n    -showShapes 0\\n    -showAttributes 0\\n    -showConnected 0\\n    -showAnimCurvesOnly 0\\n    -showMuteInfo 0\\n    -autoExpand 0\\n    -showDagOnly 1\\n    -ignoreDagHierarchy 0\\n    -expandConnections 0\\n    -showUnitlessCurves 1\\n    -showCompounds 1\\n    -showLeafs 1\\n    -showNumericAttrsOnly 0\\n    -highlightActive 1\\n    -autoSelectNewObjects 0\\n    -doNotSelectNewObjects 0\\n    -dropIsParent 1\\n    -transmitFilters 0\\n    -setFilter \\\"defaultSetFilter\\\" \\n    -showSetMembers 1\\n    -allowMultiSelection 1\\n    -alwaysToggleSelect 0\\n    -directSelect 0\\n    -displayMode \\\"DAG\\\" \\n    -expandObjects 0\\n    -setsIgnoreFilters 1\\n    -editAttrName 0\\n    -showAttrValues 0\\n    -highlightSecondary 0\\n    -showUVAttrsOnly 0\\n    -showTextureNodesOnly 0\\n    -attrAlphaOrder \\\"default\\\" \\n    -sortOrder \\\"none\\\" \\n    -longNames 0\\n    -niceNames 1\\n    -showNamespace 1\\n    $editorName\"\n"
		+ "\t\t\t\t\t\"outlinerPanel -edit -l (localizedPanelLabel(\\\"Outliner\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\noutlinerEditor -e \\n    -showShapes 0\\n    -showAttributes 0\\n    -showConnected 0\\n    -showAnimCurvesOnly 0\\n    -showMuteInfo 0\\n    -autoExpand 0\\n    -showDagOnly 1\\n    -ignoreDagHierarchy 0\\n    -expandConnections 0\\n    -showUnitlessCurves 1\\n    -showCompounds 1\\n    -showLeafs 1\\n    -showNumericAttrsOnly 0\\n    -highlightActive 1\\n    -autoSelectNewObjects 0\\n    -doNotSelectNewObjects 0\\n    -dropIsParent 1\\n    -transmitFilters 0\\n    -setFilter \\\"defaultSetFilter\\\" \\n    -showSetMembers 1\\n    -allowMultiSelection 1\\n    -alwaysToggleSelect 0\\n    -directSelect 0\\n    -displayMode \\\"DAG\\\" \\n    -expandObjects 0\\n    -setsIgnoreFilters 1\\n    -editAttrName 0\\n    -showAttrValues 0\\n    -highlightSecondary 0\\n    -showUVAttrsOnly 0\\n    -showTextureNodesOnly 0\\n    -attrAlphaOrder \\\"default\\\" \\n    -sortOrder \\\"none\\\" \\n    -longNames 0\\n    -niceNames 1\\n    -showNamespace 1\\n    $editorName\"\n"
		+ "\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Persp View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"wireframe\\\" \\n    -activeOnly 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 1\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 0\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 16384\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -maxConstantTransparency 1\\n    -rendererName \\\"base_OpenGL_Renderer\\\" \\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -shadows 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"wireframe\\\" \\n    -activeOnly 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 1\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 0\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 16384\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -maxConstantTransparency 1\\n    -rendererName \\\"base_OpenGL_Renderer\\\" \\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -shadows 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName\"\n"
		+ "\t\t\t\t$configName;\n\n            setNamedPanelLayout (localizedPanelLabel(\"Current Layout\"));\n        }\n\n        panelHistory -e -clear mainPanelHistory;\n        setFocus `paneLayout -q -p1 $gMainPane`;\n        sceneUIReplacement -deleteRemaining;\n        sceneUIReplacement -clear;\n\t}\n\n\ngrid -spacing 3.2 -size 12 -divisions 4 -displayAxes yes -displayGridLines yes -displayDivisionLines yes -displayPerspectiveLabels no -displayOrthographicLabels no -displayAxesBold yes -perspectiveLabelPosition axis -orthographicLabelPosition edge;\n}\n");
	setAttr ".st" 3;
createNode script -n "sceneConfigurationScriptNode";
	setAttr ".b" -type "string" "playbackOptions -min 1 -max 24 -ast 1 -aet 48 ";
	setAttr ".st" 6;
createNode renderLayer -n "RanderLayerLightmap";
	setAttr ".do" 1;
createNode lambert -n "RenderLambert";
	setAttr ".c" -type "float3" 1 1 1 ;
createNode shadingEngine -n "RenderLambertSG";
	setAttr ".ihi" 0;
	setAttr ".ro" yes;
createNode materialInfo -n "materialInfo3";
createNode objectSet -n "Default";
	addAttr -ci true -sn "ExportPath" -ln "ExportPath" -dt "string";
	addAttr -ci true -sn "DaeOutputPath" -ln "DaeOutputPath" -dt "string";
	addAttr -ci true -sn "Visible" -ln "Visible" -dv 1 -at "long";
	addAttr -ci true -sn "Texturing" -ln "Texturing" -dv 1 -at "long";
	addAttr -ci true -sn "Shading" -ln "Shading" -dv 1 -at "long";
	addAttr -ci true -sn "Bounding_box" -ln "Bounding_box" -at "long";
	addAttr -ci true -sn "Color" -ln "Color" -dv 7 -at "long";
	addAttr -ci true -sn "Display_Type" -ln "Display_Type" -dv 1 -at "long";
	addAttr -ci true -sn "Exporting" -ln "Exporting" -dv 1 -at "long";
	addAttr -ci true -sn "ExportingPhysics" -ln "ExportingPhysics" -at "long";
	addAttr -ci true -sn "PutToRenderLayer" -ln "PutToRenderLayer" -at "long";
	addAttr -ci true -sn "UVSetName" -ln "UVSetName" -dt "string";
	addAttr -ci true -sn "TextureWidth" -ln "TextureWidth" -dv 1024 -at "long";
	addAttr -ci true -sn "TextureHeight" -ln "TextureHeight" -dv 1024 -at "long";
	addAttr -ci true -sn "MinShellSize" -ln "MinShellSize" -dv 1 -at "double";
	addAttr -ci true -sn "PixelBetweenShells" -ln "PixelBetweenShells" -dv 2 -at "double";
	addAttr -ci true -sn "PositionEpsilon" -ln "PositionEpsilon" -at "float2" -nc 2;
	addAttr -ci true -sn "epsilonePA" -ln "epsilonePA" -at "float" -p "PositionEpsilon";
	addAttr -ci true -sn "epsilonePB" -ln "epsilonePB" -at "float" -p "PositionEpsilon";
	addAttr -ci true -sn "NormalsEpsilon" -ln "NormalsEpsilon" -at "float2" -nc 2;
	addAttr -ci true -sn "epsiloneNA" -ln "epsiloneNA" -at "float" -p "NormalsEpsilon";
	addAttr -ci true -sn "epsiloneNB" -ln "epsiloneNB" -at "float" -p "NormalsEpsilon";
	addAttr -ci true -sn "UVEpsilon" -ln "UVEpsilon" -at "float2" -nc 2;
	addAttr -ci true -sn "epsiloneUVA" -ln "epsiloneUVA" -at "float" -p "UVEpsilon";
	addAttr -ci true -sn "epsiloneUVB" -ln "epsiloneUVB" -at "float" -p "UVEpsilon";
	addAttr -ci true -sn "PreProductConnectShels" -ln "PreProductConnectShels" -dv 1 
		-at "long";
	addAttr -ci true -sn "PreProductCheckNormals" -ln "PreProductCheckNormals" -dv 1 
		-at "long";
	addAttr -ci true -sn "PostProductScaleShels" -ln "PostProductScaleShels" -dv 1 -at "long";
	addAttr -ci true -sn "LightmapFilePath" -ln "LightmapFilePath" -dt "string";
	addAttr -ci true -sn "GrayLightmap" -ln "GrayLightmap" -dv 1 -at "long";
	addAttr -ci true -sn "RenderType" -ln "RenderType" -dv 1 -at "long";
	addAttr -ci true -sn "RenderImageFormat" -ln "RenderImageFormat" -dv 1 -at "long";
	addAttr -ci true -sn "FullShading" -ln "FullShading" -at "long";
	addAttr -ci true -sn "Illumination" -ln "Illumination" -dv 1 -at "long";
	addAttr -ci true -sn "IndirectIllumination" -ln "IndirectIllumination" -at "long";
	addAttr -ci true -sn "RNM" -ln "RNM" -at "long";
	addAttr -ci true -sn "RenderCustom" -ln "RenderCustom" -at "long";
	addAttr -ci true -sn "RenderCustomShader" -ln "RenderCustomShader" -dt "string";
	addAttr -ci true -sn "EnableColorFilter" -ln "EnableColorFilter" -at "long";
	addAttr -ci true -sn "FilterSize" -ln "FilterSize" -dv 0.05 -at "double";
	addAttr -ci true -sn "FilterShape" -ln "FilterShape" -dv 1.1 -at "double";
	addAttr -ci true -sn "FilterNormalDeviation" -ln "FilterNormalDeviation" -dv 6.2 
		-at "double";
	addAttr -ci true -sn "ReferenceMappingType" -ln "ReferenceMappingType" -dv 1 -at "long";
	addAttr -ci true -sn "VisibleStartDistance" -ln "VisibleStartDistance" -at "double";
	addAttr -ci true -sn "makePartitions" -ln "makePartitions" -dv 1 -at "long";
	addAttr -ci true -sn "UseAspectGeneration" -ln "UseAspectGeneration" -at "long";
	addAttr -ci true -sn "CurrentAspectType" -ln "CurrentAspectType" -dv 1 -at "long";
	addAttr -ci true -sn "ModelInfluenceBonesNumber" -ln "ModelInfluenceBonesNumber" 
		-at "long";
	addAttr -ci true -sn "ModelNumAnimations" -ln "ModelNumAnimations" -at "long";
	setAttr ".ihi" 0;
	setAttr ".an" -type "string" "gCharacterSet";
	setAttr ".ExportPath" -type "string" "models/misc/no_model_Default";
	setAttr ".DaeOutputPath" -type "string" "_Default";
	setAttr ".UVSetName" -type "string" "uvSet";
	setAttr ".PositionEpsilon" -type "float2" 1 100 ;
	setAttr ".NormalsEpsilon" -type "float2" 1 100 ;
	setAttr ".UVEpsilon" -type "float2" 1 100000 ;
	setAttr ".LightmapFilePath" -type "string" "lightmaps/Default";
	setAttr ".RenderCustomShader" -type "string" "";
createNode objectSet -n "PhysicsScene";
	addAttr -ci true -sn "GlobalColor" -ln "GlobalColor" -dv 1 -at "long";
	addAttr -ci true -sn "CurrentSet" -ln "CurrentSet" -dt "string";
	setAttr ".ihi" 0;
	setAttr ".an" -type "string" "gCharacterSet";
	setAttr ".CurrentSet" -type "string" "";
createNode objectSet -n "Default_set";
	addAttr -ci true -sn "ExportPath" -ln "ExportPath" -dt "string";
	addAttr -ci true -sn "DaeOutputPath" -ln "DaeOutputPath" -dt "string";
	addAttr -ci true -sn "Visible" -ln "Visible" -dv 1 -at "long";
	addAttr -ci true -sn "Texturing" -ln "Texturing" -dv 1 -at "long";
	addAttr -ci true -sn "Shading" -ln "Shading" -dv 1 -at "long";
	addAttr -ci true -sn "Bounding_box" -ln "Bounding_box" -at "long";
	addAttr -ci true -sn "Color" -ln "Color" -dv 7 -at "long";
	addAttr -ci true -sn "Display_Type" -ln "Display_Type" -dv 1 -at "long";
	addAttr -ci true -sn "Exporting" -ln "Exporting" -dv 1 -at "long";
	addAttr -ci true -sn "ExportingPhysics" -ln "ExportingPhysics" -at "long";
	addAttr -ci true -sn "PutToRenderLayer" -ln "PutToRenderLayer" -dv 1 -at "long";
	addAttr -ci true -sn "UVSetName" -ln "UVSetName" -dt "string";
	addAttr -ci true -sn "TextureWidth" -ln "TextureWidth" -dv 1024 -at "long";
	addAttr -ci true -sn "TextureHeight" -ln "TextureHeight" -dv 1024 -at "long";
	addAttr -ci true -sn "MinShellSize" -ln "MinShellSize" -dv 1 -at "double";
	addAttr -ci true -sn "PixelBetweenShells" -ln "PixelBetweenShells" -dv 2 -at "double";
	addAttr -ci true -sn "PositionEpsilon" -ln "PositionEpsilon" -at "float2" -nc 2;
	addAttr -ci true -sn "epsilonePA" -ln "epsilonePA" -at "float" -p "PositionEpsilon";
	addAttr -ci true -sn "epsilonePB" -ln "epsilonePB" -at "float" -p "PositionEpsilon";
	addAttr -ci true -sn "NormalsEpsilon" -ln "NormalsEpsilon" -at "float2" -nc 2;
	addAttr -ci true -sn "epsiloneNA" -ln "epsiloneNA" -at "float" -p "NormalsEpsilon";
	addAttr -ci true -sn "epsiloneNB" -ln "epsiloneNB" -at "float" -p "NormalsEpsilon";
	addAttr -ci true -sn "UVEpsilon" -ln "UVEpsilon" -at "float2" -nc 2;
	addAttr -ci true -sn "epsiloneUVA" -ln "epsiloneUVA" -at "float" -p "UVEpsilon";
	addAttr -ci true -sn "epsiloneUVB" -ln "epsiloneUVB" -at "float" -p "UVEpsilon";
	addAttr -ci true -sn "PreProductConnectShels" -ln "PreProductConnectShels" -dv 1 
		-at "long";
	addAttr -ci true -sn "PreProductCheckNormals" -ln "PreProductCheckNormals" -dv 1 
		-at "long";
	addAttr -ci true -sn "PostProductScaleShels" -ln "PostProductScaleShels" -dv 1 -at "long";
	addAttr -ci true -sn "LightmapFilePath" -ln "LightmapFilePath" -dt "string";
	addAttr -ci true -sn "GrayLightmap" -ln "GrayLightmap" -dv 1 -at "long";
	addAttr -ci true -sn "RenderType" -ln "RenderType" -dv 1 -at "long";
	addAttr -ci true -sn "RenderImageFormat" -ln "RenderImageFormat" -dv 1 -at "long";
	addAttr -ci true -sn "FullShading" -ln "FullShading" -at "long";
	addAttr -ci true -sn "Illumination" -ln "Illumination" -dv 1 -at "long";
	addAttr -ci true -sn "IndirectIllumination" -ln "IndirectIllumination" -at "long";
	addAttr -ci true -sn "RNM" -ln "RNM" -at "long";
	addAttr -ci true -sn "RenderCustom" -ln "RenderCustom" -at "long";
	addAttr -ci true -sn "RenderCustomShader" -ln "RenderCustomShader" -dt "string";
	addAttr -ci true -sn "EnableColorFilter" -ln "EnableColorFilter" -at "long";
	addAttr -ci true -sn "FilterSize" -ln "FilterSize" -dv 0.05 -at "double";
	addAttr -ci true -sn "FilterShape" -ln "FilterShape" -dv 1.1 -at "double";
	addAttr -ci true -sn "FilterNormalDeviation" -ln "FilterNormalDeviation" -dv 6.2 
		-at "double";
	addAttr -ci true -sn "ReferenceMappingType" -ln "ReferenceMappingType" -dv 1 -at "long";
	addAttr -ci true -sn "VisibleStartDistance" -ln "VisibleStartDistance" -at "double";
	addAttr -ci true -sn "makePartitions" -ln "makePartitions" -at "long";
	addAttr -ci true -sn "UseAspectGeneration" -ln "UseAspectGeneration" -at "long";
	addAttr -ci true -sn "CurrentAspectType" -ln "CurrentAspectType" -dv 1 -at "long";
	addAttr -ci true -sn "ModelInfluenceBonesNumber" -ln "ModelInfluenceBonesNumber" 
		-at "long";
	addAttr -ci true -sn "ModelNumAnimations" -ln "ModelNumAnimations" -at "long";
	setAttr ".ihi" 0;
	setAttr ".mwc" 1;
	setAttr ".an" -type "string" "gCharacterSet";
	setAttr ".ExportPath" -type "string" "models/misc/no_model_Default_set";
	setAttr ".DaeOutputPath" -type "string" "_Default_set";
	setAttr ".UVSetName" -type "string" "uvSet";
	setAttr ".PositionEpsilon" -type "float2" 1 100 ;
	setAttr ".NormalsEpsilon" -type "float2" 1 100 ;
	setAttr ".UVEpsilon" -type "float2" 1 100000 ;
	setAttr ".LightmapFilePath" -type "string" "lightmaps/Default_set";
	setAttr ".RenderCustomShader" -type "string" "";
createNode partition -n "VisualScenePartition";
createNode objectSet -n "no_model";
	addAttr -ci true -sn "ExportPath" -ln "ExportPath" -dt "string";
	addAttr -ci true -sn "DaeOutputPath" -ln "DaeOutputPath" -dt "string";
	addAttr -ci true -sn "Visible" -ln "Visible" -dv 1 -at "long";
	addAttr -ci true -sn "Texturing" -ln "Texturing" -dv 1 -at "long";
	addAttr -ci true -sn "Shading" -ln "Shading" -dv 1 -at "long";
	addAttr -ci true -sn "Bounding_box" -ln "Bounding_box" -at "long";
	addAttr -ci true -sn "Color" -ln "Color" -dv 7 -at "long";
	addAttr -ci true -sn "Display_Type" -ln "Display_Type" -dv 1 -at "long";
	addAttr -ci true -sn "Exporting" -ln "Exporting" -dv 1 -at "long";
	addAttr -ci true -sn "ExportingPhysics" -ln "ExportingPhysics" -at "long";
	addAttr -ci true -sn "PutToRenderLayer" -ln "PutToRenderLayer" -dv 1 -at "long";
	addAttr -ci true -sn "UVSetName" -ln "UVSetName" -dt "string";
	addAttr -ci true -sn "TextureWidth" -ln "TextureWidth" -dv 1024 -at "long";
	addAttr -ci true -sn "TextureHeight" -ln "TextureHeight" -dv 1024 -at "long";
	addAttr -ci true -sn "MinShellSize" -ln "MinShellSize" -dv 1 -at "double";
	addAttr -ci true -sn "PixelBetweenShells" -ln "PixelBetweenShells" -dv 2 -at "double";
	addAttr -ci true -sn "PositionEpsilon" -ln "PositionEpsilon" -at "float2" -nc 2;
	addAttr -ci true -sn "epsilonePA" -ln "epsilonePA" -at "float" -p "PositionEpsilon";
	addAttr -ci true -sn "epsilonePB" -ln "epsilonePB" -at "float" -p "PositionEpsilon";
	addAttr -ci true -sn "NormalsEpsilon" -ln "NormalsEpsilon" -at "float2" -nc 2;
	addAttr -ci true -sn "epsiloneNA" -ln "epsiloneNA" -at "float" -p "NormalsEpsilon";
	addAttr -ci true -sn "epsiloneNB" -ln "epsiloneNB" -at "float" -p "NormalsEpsilon";
	addAttr -ci true -sn "UVEpsilon" -ln "UVEpsilon" -at "float2" -nc 2;
	addAttr -ci true -sn "epsiloneUVA" -ln "epsiloneUVA" -at "float" -p "UVEpsilon";
	addAttr -ci true -sn "epsiloneUVB" -ln "epsiloneUVB" -at "float" -p "UVEpsilon";
	addAttr -ci true -sn "PreProductConnectShels" -ln "PreProductConnectShels" -dv 1 
		-at "long";
	addAttr -ci true -sn "PreProductCheckNormals" -ln "PreProductCheckNormals" -dv 1 
		-at "long";
	addAttr -ci true -sn "PostProductScaleShels" -ln "PostProductScaleShels" -dv 1 -at "long";
	addAttr -ci true -sn "LightmapFilePath" -ln "LightmapFilePath" -dt "string";
	addAttr -ci true -sn "GrayLightmap" -ln "GrayLightmap" -dv 1 -at "long";
	addAttr -ci true -sn "RenderType" -ln "RenderType" -dv 1 -at "long";
	addAttr -ci true -sn "RenderImageFormat" -ln "RenderImageFormat" -dv 1 -at "long";
	addAttr -ci true -sn "FullShading" -ln "FullShading" -at "long";
	addAttr -ci true -sn "Illumination" -ln "Illumination" -dv 1 -at "long";
	addAttr -ci true -sn "IndirectIllumination" -ln "IndirectIllumination" -at "long";
	addAttr -ci true -sn "RNM" -ln "RNM" -at "long";
	addAttr -ci true -sn "RenderCustom" -ln "RenderCustom" -at "long";
	addAttr -ci true -sn "RenderCustomShader" -ln "RenderCustomShader" -dt "string";
	addAttr -ci true -sn "EnableColorFilter" -ln "EnableColorFilter" -at "long";
	addAttr -ci true -sn "FilterSize" -ln "FilterSize" -dv 0.05 -at "double";
	addAttr -ci true -sn "FilterShape" -ln "FilterShape" -dv 1.1 -at "double";
	addAttr -ci true -sn "FilterNormalDeviation" -ln "FilterNormalDeviation" -dv 6.2 
		-at "double";
	addAttr -ci true -sn "ReferenceMappingType" -ln "ReferenceMappingType" -dv 1 -at "long";
	addAttr -ci true -sn "VisibleStartDistance" -ln "VisibleStartDistance" -at "double";
	addAttr -ci true -sn "makePartitions" -ln "makePartitions" -dv 1 -at "long";
	addAttr -ci true -sn "UseAspectGeneration" -ln "UseAspectGeneration" -at "long";
	addAttr -ci true -sn "CurrentAspectType" -ln "CurrentAspectType" -dv 1 -at "long";
	addAttr -ci true -sn "ModelInfluenceBonesNumber" -ln "ModelInfluenceBonesNumber" 
		-at "long";
	addAttr -ci true -sn "ModelNumAnimations" -ln "ModelNumAnimations" -at "long";
	setAttr ".ihi" 0;
	setAttr -s 2 ".dsm";
	setAttr ".mwc" 1;
	setAttr ".an" -type "string" "gCharacterSet";
	setAttr ".ExportPath" -type "string" "models/misc/no_model";
	setAttr ".DaeOutputPath" -type "string" "";
	setAttr ".ExportingPhysics" 1;
	setAttr ".UVSetName" -type "string" "uvSet";
	setAttr ".PositionEpsilon" -type "float2" 1 100 ;
	setAttr ".NormalsEpsilon" -type "float2" 1 100 ;
	setAttr ".UVEpsilon" -type "float2" 1 100000 ;
	setAttr ".LightmapFilePath" -type "string" "lightmaps/no_model";
	setAttr ".RenderCustomShader" -type "string" "";
createNode partition -n "PhysicsScenePartition";
select -ne :time1;
	setAttr ".o" 1;
select -ne :renderPartition;
	setAttr -s 5 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 4 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :lightList1;
select -ne :defaultTextureList1;
select -ne :initialShadingGroup;
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :hardwareRenderGlobals;
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
select -ne :defaultHardwareRenderGlobals;
	setAttr ".fn" -type "string" "im";
	setAttr ".res" -type "string" "ntsc_4d 646 485 1.333";
connectAttr "colladaDocuments.doc[0].e[2]" "pCube1.dae";
connectAttr "RanderLayerLightmap.ri" "pCube1.rlio[0]";
connectAttr "colladaDocuments.doc[0].e[1]" "pCubeShape1.dae";
connectAttr "collisionShape1.st" "collision1.shapeType";
connectAttr "collisionShape1.sx" "collision1.boxScaleX";
connectAttr "collisionShape1.sy" "collision1.boxScaleY";
connectAttr "collisionShape1.sz" "collision1.boxScaleZ";
connectAttr "collisionShape1.ptax" "collision1.point1X";
connectAttr "collisionShape1.ptay" "collision1.point1Y";
connectAttr "collisionShape1.ptaz" "collision1.point1Z";
connectAttr "collisionShape1.ptbx" "collision1.point2X";
connectAttr "collisionShape1.ptby" "collision1.point2Y";
connectAttr "collisionShape1.ptbz" "collision1.point2Z";
connectAttr "collisionShape1.rad" "collision1.radius";
connectAttr "RanderLayerLightmap.ri" "collision1.rlio[0]";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[0].llnk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.lnk[0].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[1].llnk";
connectAttr ":initialParticleSE.msg" "lightLinker1.lnk[1].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[2].llnk";
connectAttr "colladafxPasses1SG.msg" "lightLinker1.lnk[2].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[3].llnk";
connectAttr "colladafxShader2SG.msg" "lightLinker1.lnk[3].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.lnk[4].llnk";
connectAttr "RenderLambertSG.msg" "lightLinker1.lnk[4].olnk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[0].sllk";
connectAttr ":initialShadingGroup.msg" "lightLinker1.slnk[0].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[1].sllk";
connectAttr ":initialParticleSE.msg" "lightLinker1.slnk[1].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[2].sllk";
connectAttr "colladafxPasses1SG.msg" "lightLinker1.slnk[2].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[3].sllk";
connectAttr "colladafxShader2SG.msg" "lightLinker1.slnk[3].solk";
connectAttr ":defaultLightSet.msg" "lightLinker1.slnk[4].sllk";
connectAttr "RenderLambertSG.msg" "lightLinker1.slnk[4].solk";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "place2dTexture1.o" "file1.uv";
connectAttr "place2dTexture1.ofs" "file1.fs";
connectAttr "place2dTexture1.vt1" "file1.vt1";
connectAttr "place2dTexture1.vt2" "file1.vt2";
connectAttr "place2dTexture1.vt3" "file1.vt3";
connectAttr "place2dTexture1.vc1" "file1.vc1";
connectAttr "place2dTexture1.of" "file1.of";
connectAttr "place2dTexture1.s" "file1.s";
connectAttr "place2dTexture1.c" "file1.c";
connectAttr "place2dTexture1.tf" "file1.tf";
connectAttr "place2dTexture1.mv" "file1.mv";
connectAttr "place2dTexture1.mu" "file1.mu";
connectAttr "place2dTexture1.wu" "file1.wu";
connectAttr "place2dTexture1.wv" "file1.wv";
connectAttr "place2dTexture1.n" "file1.n";
connectAttr "place2dTexture1.r" "file1.ro";
connectAttr "place2dTexture1.re" "file1.re";
connectAttr "file1.oc" "colladafxShader2.DiffuseSampler";
connectAttr "colladafxPasses1SG.msg" "materialInfo1.sg";
connectAttr "Default_set.msg" "VisualScene.dnsm" -na;
connectAttr "no_model.msg" "VisualScene.dnsm" -na;
connectAttr "colladafxShader2.oc" "colladafxShader2SG.ss";
connectAttr "pCubeShape1.iog" "colladafxShader2SG.dsm" -na;
connectAttr "colladafxShader2SG.msg" "materialInfo2.sg";
connectAttr "colladafxShader2.msg" "materialInfo2.m";
connectAttr "renderLayerManager.rlmi[1]" "RanderLayerLightmap.rlid";
connectAttr "RenderLambertSG.msg" "RanderLayerLightmap.sgo";
connectAttr "RenderLambert.oc" "RenderLambertSG.ss";
connectAttr "RenderLambertSG.msg" "materialInfo3.sg";
connectAttr "RenderLambert.msg" "materialInfo3.m";
connectAttr "collision1.iog" "Default.dsm" -na;
connectAttr "Default.msg" "PhysicsScene.dnsm" -na;
connectAttr "pCube1.iog" "no_model.dsm" -na;
connectAttr "collision1.iog" "no_model.dsm" -na;
connectAttr "colladafxPasses1SG.pa" ":renderPartition.st" -na;
connectAttr "colladafxShader2SG.pa" ":renderPartition.st" -na;
connectAttr "RenderLambertSG.pa" ":renderPartition.st" -na;
connectAttr "colladafxShader2.msg" ":defaultShaderList1.s" -na;
connectAttr "RenderLambert.msg" ":defaultShaderList1.s" -na;
connectAttr "lightLinker1.msg" ":lightList1.ln" -na;
connectAttr "file1.msg" ":defaultTextureList1.tx" -na;
// End of no_model.ma
