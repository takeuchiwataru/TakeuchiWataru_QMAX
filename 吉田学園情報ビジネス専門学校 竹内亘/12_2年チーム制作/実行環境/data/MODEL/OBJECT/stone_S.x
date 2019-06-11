xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 33;
 -20.48960;-1.16000;-24.33040;,
 -20.48960;14.04640;-24.33040;,
 2.28560;14.04640;-18.59680;,
 2.28560;-1.16000;-21.04240;,
 20.85920;14.04640;-21.15360;,
 20.85920;-1.16000;-21.15360;,
 -18.16960;29.25280;-17.23920;,
 2.28560;29.25280;-18.59680;,
 23.36880;29.25280;-15.67440;,
 -24.75440;29.25280;5.39120;,
 6.71760;43.97840;9.24240;,
 29.32560;40.65840;2.73120;,
 -16.72560;29.25280;27.71360;,
 2.28560;40.65840;31.03040;,
 20.46720;45.06720;24.53200;,
 -16.72560;14.04640;27.71360;,
 2.28560;14.04640;31.03040;,
 19.81360;21.39120;24.88960;,
 -16.72560;-1.16000;29.12720;,
 2.28560;-1.16000;32.44400;,
 29.32560;-1.16000;31.03040;,
 29.32560;-1.16000;2.73120;,
 29.32560;14.04640;2.73120;,
 19.81360;21.39120;24.88960;,
 29.32560;-1.16000;31.03040;,
 29.32560;40.65840;2.73120;,
 20.46720;45.06720;24.53200;,
 -16.72560;-1.16000;29.12720;,
 -16.72560;14.04640;27.71360;,
 -24.75440;14.04640;5.39120;,
 -24.75440;-1.16000;6.80480;,
 -16.72560;29.25280;27.71360;,
 -24.75440;29.25280;5.39120;;
 
 20;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;1,6,7,2;,
 4;2,7,8,4;,
 4;6,9,10,7;,
 4;7,10,11,8;,
 4;9,12,13,10;,
 4;10,13,14,11;,
 4;12,15,16,13;,
 4;13,16,17,14;,
 4;15,18,19,16;,
 4;16,19,20,17;,
 4;21,22,23,24;,
 4;5,4,22,21;,
 4;22,25,26,23;,
 4;4,8,25,22;,
 4;27,28,29,30;,
 4;30,29,1,0;,
 4;28,31,32,29;,
 4;29,32,6,1;;
 
 MeshMaterialList {
  1;
  20;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  41;
  0.192882;0.077383;-0.978166;,
  0.061630;0.078924;-0.994974;,
  -0.070700;0.079084;-0.994358;,
  0.137983;0.138017;-0.980771;,
  0.050616;0.129881;-0.990237;,
  -0.036976;0.120753;-0.991994;,
  0.082160;0.197727;-0.976808;,
  0.036187;0.445603;-0.894499;,
  0.009654;0.569381;-0.822017;,
  -0.362423;0.925713;-0.108186;,
  -0.192843;0.962100;-0.192806;,
  -0.015437;0.962593;-0.270510;,
  -0.477364;0.873991;0.090904;,
  -0.271190;0.961942;0.033506;,
  -0.050498;0.998394;-0.025685;,
  -0.171690;0.045646;0.984093;,
  0.028292;0.078925;0.996479;,
  0.511706;0.076696;0.855731;,
  -0.171153;0.091196;0.981015;,
  -0.025864;0.154297;0.987686;,
  0.120076;0.213519;0.969531;,
  -0.994626;0.012950;0.102723;,
  0.987153;0.115096;-0.110823;,
  0.997903;0.051553;-0.039149;,
  -0.995815;0.034243;0.084737;,
  -0.227360;0.926037;-0.301269;,
  -0.171869;0.000000;0.985120;,
  0.083317;0.001284;0.996522;,
  0.686286;-0.004055;0.727320;,
  0.967515;0.222700;0.119667;,
  0.942538;0.000000;-0.334100;,
  0.944789;-0.008790;-0.327563;,
  0.999266;-0.014691;0.035385;,
  0.946921;-0.017578;-0.320985;,
  -0.940520;0.031447;0.338281;,
  -0.940869;0.015725;0.338407;,
  -0.983231;0.050474;-0.175243;,
  -0.990290;-0.006307;-0.138871;,
  -0.940985;0.000000;0.338448;,
  -0.996229;0.055745;0.066483;,
  -0.971651;0.107024;-0.210809;;
  20;
  4;0,3,4,1;,
  4;1,4,5,2;,
  4;3,6,7,4;,
  4;4,7,8,5;,
  4;25,9,10,25;,
  4;7,10,11,8;,
  4;9,12,13,10;,
  4;10,13,14,11;,
  4;26,15,16,27;,
  4;27,16,17,28;,
  4;15,18,19,16;,
  4;16,19,20,17;,
  4;22,23,29,29;,
  4;30,31,23,22;,
  4;23,32,28,17;,
  4;31,33,32,23;,
  4;34,35,24,21;,
  4;21,24,36,37;,
  4;35,38,39,24;,
  4;24,39,40,36;;
 }
 MeshTextureCoords {
  33;
  0.375000;1.000000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.500000;1.000000;,
  0.625000;0.875000;,
  0.625000;1.000000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;1.000000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  0.875000;1.000000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  0.125000;1.000000;,
  0.125000;0.875000;,
  0.250000;0.875000;,
  0.250000;1.000000;,
  0.125000;0.750000;,
  0.250000;0.750000;;
 }
}
