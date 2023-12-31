load("@//build_defs:expand_template.bzl", "expand_template")

DEFINES = [
    "ASSIMP_BUILD_NO_C4D_IMPORTER",
    # "ASSIMP_BUILD_NO_Q3BSP_IMPORTER",
    # "ASSIMP_BUILD_NO_3MF_IMPORTER",
    # "ASSIMP_BUILD_NO_ASSBIN_IMPORTER",
    # "ASSIMP_BUILD_NO_IFC_IMPORTER",
    # "ASSIMP_BUILD_NO_XGL_IMPORTER",
    # "ASSIMP_BUILD_NO_ASSBIN_EXPORTER",
    # "ASSIMP_BUILD_NO_ASSXML_EXPORTER",
]

# This is pretty awful, but assimp uses some ridiculous relative paths in its
# includes that Bazel has trouble with otherwise.
ALL_HDRS = glob([
    "code/**/*.h",
    "code/**/*.hpp",
    "code/**/*.inl",
    "include/**/*.h",
    "include/**/*.hpp",
    "include/**/*.inl",
    "contrib/**/*.h",
    "contrib/**/*.hpp",
    "contrib/**/*.inl",
])

expand_template(
    name = "config_tmpl",
    out = "include/assimp/config.h",
    substitutions = {"#cmakedefine": "// #undef"},
    template = "include/assimp/config.h.in",
)

expand_template(
    name = "revision_tmpl",
    out = "revision.h",
    substitutions = {
        "@GIT_COMMIT_HASH@": "eb8639d",
        "@GIT_BRANCH@": "master",
    },
    template = "revision.h.in",
)

cc_library(
    name = "revision",
    hdrs = [":revision_tmpl"],
)

cc_library(
    name = "includes",
    hdrs = glob([
        "include/**/*.h",
        "include/**/*.hpp",
        "include/**/*.inl",
    ]) + [
        ":config_tmpl",
    ],
    strip_include_prefix = "include",
)

cc_library(
    name = "code_includes",
    hdrs = glob([
        "code/*.h",
        "code/*.hpp",
        "code/*.inl",
    ]),
    strip_include_prefix = "code",
)

cc_library(
    name = "contrib_includes",
    hdrs = glob([
        "contrib/**/*.h",
        "contrib/**/*.hpp",
    ]),
    strip_include_prefix = "",
)

cc_library(
    name = "openddlparser",
    srcs = glob([
        "contrib/openddlparser/code/*.cpp",
    ]),
    hdrs = glob([
        "contrib/openddlparser/include/**/*.h",
        "contrib/openddlparser/include/**/*.hpp",
    ]),
    strip_include_prefix = "contrib/openddlparser/include",
    alwayslink = True,
)

cc_library(
    name = "rapidjson",
    hdrs = glob([
        "contrib/rapidjson/include/**/*.h",
    ]),
    strip_include_prefix = "contrib/rapidjson/include",
)

cc_library(
    name = "core",
    srcs = ["code/Assimp.cpp"],
    hdrs = glob(["code/*.h"]),
    defines = DEFINES,
    deps = [":includes"],
    alwayslink = True,
)

cc_library(
    name = "irrxml",
    srcs = glob([
        "contrib/irrXML/irrXML.cpp",
        "code/**/*.h",
    ]),
    hdrs = glob([
        "contrib/irrXML/*.h",
        "contrib/irrXML/*.hpp",
    ]),
    strip_include_prefix = "contrib/irrXML",
    deps = [":includes"],
    alwayslink = True,
)

cc_library(
    name = "unzip",
    srcs = glob([
        "contrib/unzip/*.c",
        "contrib/zlib/*.c",
    ]),
    hdrs = glob([
        "contrib/unzip/*.h",
        "contrib/zlib/*.h",
    ]),
    alwayslink = True,
)

cc_library(
    name = "poly2tri",
    srcs = glob([
        "contrib/poly2tri/**/*.h",
        "contrib/poly2tri/**/*.cc",
    ]),
    alwayslink = True,
)

cc_library(
    name = "clipper",
    srcs = glob([
        "contrib/clipper/*.hpp",
        "contrib/clipper/*.cpp",
    ]),
    alwayslink = True,
)

cc_library(
    name = "open3dgc",
    srcs = glob([
        "contrib/Open3DGC/*.cpp",
    ]),
    hdrs = glob([
        "contrib/Open3DGC/*.h",
        "contrib/Open3DGC/*.inl",
    ]),
    alwayslink = True,
)

cc_library(
    name = "common",
    srcs = [
        "code/BaseImporter.cpp",
        "code/BaseProcess.cpp",
        "code/Bitmap.cpp",
        "code/CInterfaceIOWrapper.cpp",
        "code/CreateAnimMesh.cpp",
        "code/DefaultIOStream.cpp",
        "code/DefaultIOSystem.cpp",
        "code/Importer.cpp",
        "code/ImporterRegistry.cpp",
        "code/PostStepRegistry.cpp",
        "code/RemoveComments.cpp",
        "code/SGSpatialSort.cpp",
        "code/SceneCombiner.cpp",
        "code/ScenePreprocessor.cpp",
        "code/SkeletonMeshBuilder.cpp",
        "code/SpatialSort.cpp",
        "code/SplitByBoneCountProcess.cpp",
        "code/StandardShapes.cpp",
        "code/Subdivision.cpp",
        "code/TargetAnimation.cpp",
        "code/Version.cpp",
        "code/VertexTriangleAdjacency.cpp",
        "code/scene.cpp",
    ],
    hdrs = ALL_HDRS,
    defines = DEFINES,
    deps = [
        ":includes",
        ":irrxml",
        ":revision",
    ],
    alwayslink = True,
)

cc_library(
    name = "logging",
    srcs = ["code/DefaultLogger.cpp"],
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "exporter",
    srcs = [
        "code/AssimpCExport.cpp",
        "code/Exporter.cpp",
    ],
    defines = DEFINES,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "post_processing",
    srcs = [
        "code/CalcTangentsProcess.cpp",
        "code/ComputeUVMappingProcess.cpp",
        "code/ConvertToLHProcess.cpp",
        "code/DeboneProcess.cpp",
        "code/FindDegenerates.cpp",
        "code/FindInstancesProcess.cpp",
        "code/FindInvalidDataProcess.cpp",
        "code/FixNormalsStep.cpp",
        "code/GenFaceNormalsProcess.cpp",
        "code/GenVertexNormalsProcess.cpp",
        "code/ImproveCacheLocality.cpp",
        "code/JoinVerticesProcess.cpp",
        "code/LimitBoneWeightsProcess.cpp",
        "code/MakeVerboseFormat.cpp",
        "code/OptimizeGraph.cpp",
        "code/OptimizeMeshes.cpp",
        "code/PretransformVertices.cpp",
        "code/ProcessHelper.cpp",
        "code/RemoveRedundantMaterials.cpp",
        "code/RemoveVCProcess.cpp",
        "code/SortByPTypeProcess.cpp",
        "code/SplitLargeMeshes.cpp",
        "code/TextureTransform.cpp",
        "code/TriangulateProcess.cpp",
        "code/ValidateDataStructure.cpp",
    ],
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "material_system",
    srcs = ["code/MaterialSystem.cpp"],
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "step_exporter",
    srcs = ["code/StepExporter.cpp"],
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "assimp",
    hdrs = glob([
        "include/assimp/**/*.h",
        "include/assimp/**/*.inl",
    ]) + [
        ":config_tmpl",
    ],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = [
        ":clipper",
        ":code_includes",
        ":common",
        ":contrib_includes",
        ":core",
        ":exporter",
        ":includes",
        ":irrxml",
        ":logging",
        ":material_system",
        ":open3dgc",
        ":openddlparser",
        ":poly2tri",
        ":post_processing",
        ":step_exporter",
        ":unzip",
        # Importers
        ":amf_importer",
        ":3ds_importer",
        ":ac_importer",
        ":ase_importer",
        ":assbin_importer",
        ":assxml_importer",
        ":b3d_importer",
        ":bvh_importer",
        ":collada_importer",
        ":dxf_importer",
        ":csm_importer",
        ":hmp_importer",
        ":irrmesh_importer",
        ":irr_importer",
        ":lwo_importer",
        ":lws_importer",
        ":md2_importer",
        ":md3_importer",
        ":md5_importer",
        ":mdc_importer",
        ":mdl_importer",
        ":nff_importer",
        ":ndo_importer",
        ":off_importer",
        ":obj_importer",
        ":ogre_importer",
        ":opengex_importer",
        ":ply_importer",
        ":ms3d_importer",
        ":cob_importer",
        ":blend_importer",
        ":ifc_importer",
        ":xgl_importer",
        ":fbx_importer",
        ":q3d_importer",
        ":q3bsp_importer",
        ":raw_importer",
        ":sib_importer",
        ":smd_importer",
        ":stl_importer",
        ":terragen_importer",
        ":3d_importer",
        ":x_importer",
        ":x3d_importer",
        ":gltf_importer",
        ":3mf_importer",
        ":mmd_importer",
    ],
)

# ========= Importers =========
# =============================

cc_library(
    name = "amf_importer",
    srcs = [
        "code/AMFImporter.cpp",
        "code/AMFImporter.hpp",
        "code/AMFImporter_Geometry.cpp",
        "code/AMFImporter_Macro.hpp",
        "code/AMFImporter_Material.cpp",
        "code/AMFImporter_Node.hpp",
        "code/AMFImporter_Postprocess.cpp",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
        ":irrxml",
    ],
    alwayslink = True,
)

cc_library(
    name = "3ds_importer",
    srcs = [
        "code/3DSConverter.cpp",
        "code/3DSExporter.cpp",
        "code/3DSExporter.h",
        "code/3DSHelper.h",
        "code/3DSLoader.cpp",
        "code/3DSLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "ac_importer",
    srcs = [
        "code/ACLoader.cpp",
        "code/ACLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "ase_importer",
    srcs = [
        "code/ASELoader.cpp",
        "code/ASELoader.h",
        "code/ASEParser.cpp",
        "code/ASEParser.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "assbin_importer",
    srcs = [
        "code/AssbinExporter.cpp",
        "code/AssbinExporter.h",
        "code/AssbinLoader.cpp",
        "code/AssbinLoader.h",
    ],
    hdrs = ALL_HDRS,
    includes = ["."],
    deps = [
        ":code_includes",
        ":contrib_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "assxml_importer",
    srcs = [
        "code/AssxmlExporter.cpp",
        "code/AssxmlExporter.h",
    ],
    hdrs = ALL_HDRS,
    includes = ["."],
    deps = [
        ":code_includes",
        ":contrib_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "b3d_importer",
    srcs = [
        "code/B3DImporter.cpp",
        "code/B3DImporter.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "bvh_importer",
    srcs = [
        "code/BVHLoader.cpp",
        "code/BVHLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "collada_importer",
    srcs = [
        "code/ColladaExporter.cpp",
        "code/ColladaExporter.h",
        "code/ColladaHelper.h",
        "code/ColladaLoader.cpp",
        "code/ColladaLoader.h",
        "code/ColladaParser.cpp",
        "code/ColladaParser.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
        ":irrxml",
    ],
    alwayslink = True,
)

cc_library(
    name = "dxf_importer",
    srcs = [
        "code/DXFHelper.h",
        "code/DXFLoader.cpp",
        "code/DXFLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "csm_importer",
    srcs = [
        "code/CSMLoader.cpp",
        "code/CSMLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "hmp_importer",
    srcs = [
        "code/HMPFileData.h",
        "code/HMPLoader.cpp",
        "code/HMPLoader.h",
        "code/HalfLifeFileData.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "irrshared",
    srcs = [
        "code/IRRShared.cpp",
        "code/IRRShared.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
        ":irrxml",
    ],
    alwayslink = True,
)

cc_library(
    name = "irrmesh_importer",
    srcs = [
        "code/IRRMeshLoader.cpp",
        "code/IRRMeshLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
        ":irrshared",
        ":irrxml",
    ],
    alwayslink = True,
)

cc_library(
    name = "irr_importer",
    srcs = [
        "code/IRRLoader.cpp",
        "code/IRRLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
        ":irrshared",
        ":irrxml",
    ],
    alwayslink = True,
)

cc_library(
    name = "lwo_importer",
    srcs = [
        "code/LWOAnimation.cpp",
        "code/LWOAnimation.h",
        "code/LWOBLoader.cpp",
        "code/LWOFileData.h",
        "code/LWOLoader.cpp",
        "code/LWOLoader.h",
        "code/LWOMaterial.cpp",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "lws_importer",
    srcs = [
        "code/LWSLoader.cpp",
        "code/LWSLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "md2_importer",
    srcs = [
        "code/MD2FileData.h",
        "code/MD2Loader.cpp",
        "code/MD2Loader.h",
        "code/MD2NormalTable.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "md3_importer",
    srcs = [
        "code/MD3FileData.h",
        "code/MD3Loader.cpp",
        "code/MD3Loader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "md5_importer",
    srcs = [
        "code/MD5Loader.cpp",
        "code/MD5Loader.h",
        "code/MD5Parser.cpp",
        "code/MD5Parser.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "mdc_importer",
    srcs = [
        "code/MDCFileData.h",
        "code/MDCLoader.cpp",
        "code/MDCLoader.h",
        "code/MDCNormalTable.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "mdl_importer",
    srcs = [
        "code/MDLDefaultColorMap.h",
        "code/MDLFileData.h",
        "code/MDLLoader.cpp",
        "code/MDLLoader.h",
        "code/MDLMaterialLoader.cpp",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "nff_importer",
    srcs = [
        "code/NFFLoader.cpp",
        "code/NFFLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "ndo_importer",
    srcs = [
        "code/NDOLoader.cpp",
        "code/NDOLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "off_importer",
    srcs = [
        "code/OFFLoader.cpp",
        "code/OFFLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "obj_importer",
    srcs = [
        "code/ObjExporter.cpp",
        "code/ObjExporter.h",
        "code/ObjFileData.h",
        "code/ObjFileImporter.cpp",
        "code/ObjFileImporter.h",
        "code/ObjFileMtlImporter.cpp",
        "code/ObjFileMtlImporter.h",
        "code/ObjFileParser.cpp",
        "code/ObjFileParser.h",
        "code/ObjTools.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "ogre_importer",
    srcs = [
        "code/OgreBinarySerializer.cpp",
        "code/OgreBinarySerializer.h",
        "code/OgreImporter.cpp",
        "code/OgreImporter.h",
        "code/OgreMaterial.cpp",
        "code/OgreParsingUtils.h",
        "code/OgreStructs.cpp",
        "code/OgreStructs.h",
        "code/OgreXmlSerializer.cpp",
        "code/OgreXmlSerializer.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
        ":irrxml",
    ],
    alwayslink = True,
)

cc_library(
    name = "opengex_importer",
    srcs = [
        "code/OpenGEXExporter.cpp",
        "code/OpenGEXExporter.h",
        "code/OpenGEXImporter.cpp",
        "code/OpenGEXImporter.h",
        "code/OpenGEXStructs.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
        ":openddlparser",
    ],
    alwayslink = True,
)

cc_library(
    name = "ply_importer",
    srcs = [
        "code/PlyExporter.cpp",
        "code/PlyExporter.h",
        "code/PlyLoader.cpp",
        "code/PlyLoader.h",
        "code/PlyParser.cpp",
        "code/PlyParser.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "ms3d_importer",
    srcs = [
        "code/MS3DLoader.cpp",
        "code/MS3DLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "cob_importer",
    srcs = [
        "code/COBLoader.cpp",
        "code/COBLoader.h",
        "code/COBScene.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "blend_importer",
    srcs = [
        "code/BlenderBMesh.cpp",
        "code/BlenderBMesh.h",
        "code/BlenderDNA.cpp",
        "code/BlenderDNA.h",
        "code/BlenderIntermediate.h",
        "code/BlenderLoader.cpp",
        "code/BlenderLoader.h",
        "code/BlenderModifier.cpp",
        "code/BlenderModifier.h",
        "code/BlenderScene.cpp",
        "code/BlenderScene.h",
        "code/BlenderSceneGen.h",
        "code/BlenderTessellator.cpp",
        "code/BlenderTessellator.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "ifc_importer",
    srcs = [
        "code/IFCBoolean.cpp",
        "code/IFCCurve.cpp",
        "code/IFCGeometry.cpp",
        "code/IFCLoader.cpp",
        "code/IFCLoader.h",
        "code/IFCMaterial.cpp",
        "code/IFCOpenings.cpp",
        "code/IFCProfile.cpp",
        "code/IFCReaderGen.h",
        "code/IFCReaderGen1.cpp",
        "code/IFCReaderGen2.cpp",
        "code/IFCUtil.cpp",
        "code/IFCUtil.h",
        "code/STEPFile.h",
        "code/STEPFileEncoding.cpp",
        "code/STEPFileEncoding.h",
        "code/STEPFileReader.cpp",
        "code/STEPFileReader.h",
    ],
    hdrs = ALL_HDRS,
    includes = ["."],
    deps = [
        ":code_includes",
        ":contrib_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "xgl_importer",
    srcs = [
        "code/XGLLoader.cpp",
        "code/XGLLoader.h",
    ],
    hdrs = ALL_HDRS,
    includes = ["."],
    deps = [
        ":code_includes",
        ":contrib_includes",
        ":includes",
        ":irrxml",
    ],
    alwayslink = True,
)

cc_library(
    name = "fbx_importer",
    srcs = [
        "code/FBXAnimation.cpp",
        "code/FBXBinaryTokenizer.cpp",
        "code/FBXCompileConfig.h",
        "code/FBXConverter.cpp",
        "code/FBXConverter.h",
        "code/FBXDeformer.cpp",
        "code/FBXDocument.cpp",
        "code/FBXDocument.h",
        "code/FBXDocumentUtil.cpp",
        "code/FBXImportSettings.h",
        "code/FBXImporter.cpp",
        "code/FBXImporter.h",
        "code/FBXMaterial.cpp",
        "code/FBXMeshGeometry.cpp",
        "code/FBXMeshGeometry.h",
        "code/FBXModel.cpp",
        "code/FBXNodeAttribute.cpp",
        "code/FBXParser.cpp",
        "code/FBXParser.h",
        "code/FBXProperties.cpp",
        "code/FBXProperties.h",
        "code/FBXTokenizer.cpp",
        "code/FBXTokenizer.h",
        "code/FBXUtil.cpp",
        "code/FBXUtil.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "q3d_importer",
    srcs = [
        "code/Q3DLoader.cpp",
        "code/Q3DLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "q3bsp_importer",
    srcs = [
        "code/Q3BSPFileData.h",
        "code/Q3BSPFileImporter.cpp",
        "code/Q3BSPFileImporter.h",
        "code/Q3BSPFileParser.cpp",
        "code/Q3BSPFileParser.h",
        "code/Q3BSPZipArchive.cpp",
        "code/Q3BSPZipArchive.h",
    ],
    hdrs = ALL_HDRS,
    includes = ["."],
    deps = [
        ":code_includes",
        ":contrib_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "raw_importer",
    srcs = [
        "code/RawLoader.cpp",
        "code/RawLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "sib_importer",
    srcs = [
        "code/SIBImporter.cpp",
        "code/SIBImporter.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "smd_importer",
    srcs = [
        "code/SMDLoader.cpp",
        "code/SMDLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "stl_importer",
    srcs = [
        "code/STLExporter.cpp",
        "code/STLExporter.h",
        "code/STLLoader.cpp",
        "code/STLLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "terragen_importer",
    srcs = [
        "code/TerragenLoader.cpp",
        "code/TerragenLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "3d_importer",
    srcs = [
        "code/UnrealLoader.cpp",
        "code/UnrealLoader.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "x_importer",
    srcs = [
        "code/XFileExporter.cpp",
        "code/XFileExporter.h",
        "code/XFileHelper.h",
        "code/XFileImporter.cpp",
        "code/XFileImporter.h",
        "code/XFileParser.cpp",
        "code/XFileParser.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)

cc_library(
    name = "x3d_importer",
    srcs = [
        "code/FIReader.cpp",
        "code/FIReader.hpp",
        "code/X3DExporter.cpp",
        "code/X3DExporter.hpp",
        "code/X3DImporter.cpp",
        "code/X3DImporter.hpp",
        "code/X3DImporter_Geometry2D.cpp",
        "code/X3DImporter_Geometry3D.cpp",
        "code/X3DImporter_Group.cpp",
        "code/X3DImporter_Light.cpp",
        "code/X3DImporter_Macro.hpp",
        "code/X3DImporter_Metadata.cpp",
        "code/X3DImporter_Networking.cpp",
        "code/X3DImporter_Node.hpp",
        "code/X3DImporter_Postprocess.cpp",
        "code/X3DImporter_Rendering.cpp",
        "code/X3DImporter_Shape.cpp",
        "code/X3DImporter_Texturing.cpp",
        "code/X3DVocabulary.cpp",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
        ":irrxml",
    ],
    alwayslink = True,
)

cc_library(
    name = "gltf_importer",
    srcs = [
        "code/glTFAsset.h",
        "code/glTFAssetWriter.h",
        "code/glTFExporter.cpp",
        "code/glTFExporter.h",
        "code/glTFImporter.cpp",
        "code/glTFImporter.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
        ":rapidjson",
    ],
    alwayslink = True,
)

cc_library(
    name = "3mf_importer",
    srcs = [
        "code/D3MFImporter.cpp",
        "code/D3MFImporter.h",
        "code/D3MFOpcPackage.cpp",
        "code/D3MFOpcPackage.h",
    ],
    hdrs = ALL_HDRS,
    includes = ["."],
    deps = [
        ":code_includes",
        ":contrib_includes",
        ":includes",
        ":irrxml",
    ],
    alwayslink = True,
)

cc_library(
    name = "mmd_importer",
    srcs = [
        "code/MMDCpp14.h",
        "code/MMDImporter.cpp",
        "code/MMDImporter.h",
        "code/MMDPmdParser.h",
        "code/MMDPmxParser.cpp",
        "code/MMDPmxParser.h",
        "code/MMDVmdParser.h",
    ],
    hdrs = ALL_HDRS,
    deps = [
        ":code_includes",
        ":includes",
    ],
    alwayslink = True,
)
