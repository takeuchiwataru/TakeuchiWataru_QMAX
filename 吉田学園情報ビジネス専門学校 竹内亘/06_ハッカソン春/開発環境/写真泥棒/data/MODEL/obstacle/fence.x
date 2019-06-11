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
 140;
 6.62364;111.70260;-6.26932;,
 6.25260;111.70260;7.89900;,
 6.25260;-0.59800;7.89900;,
 6.62364;-0.59800;-6.26932;,
 6.25260;111.70260;7.89900;,
 -7.91568;111.70260;7.52796;,
 -7.91568;-0.59800;7.52796;,
 6.25260;-0.59800;7.89900;,
 -7.91568;111.70260;7.52796;,
 -7.54468;111.70260;-6.64032;,
 -7.54468;-0.59800;-6.64032;,
 -7.91568;-0.59800;7.52796;,
 -7.54468;111.70260;-6.64032;,
 6.62364;111.70260;-6.26932;,
 6.62364;-0.59800;-6.26932;,
 -7.54468;-0.59800;-6.64032;,
 6.25260;111.70260;7.89900;,
 6.62364;111.70260;-6.26932;,
 6.62364;-0.59800;-6.26932;,
 6.25260;-0.59800;7.89900;,
 4.66780;74.61908;-18.82708;,
 4.66376;84.22408;-18.67312;,
 1.00280;83.55992;121.13205;,
 1.00684;73.95492;120.97816;,
 4.66376;84.22408;-18.67312;,
 -4.93832;84.22408;-18.92456;,
 -8.59924;83.55992;120.88068;,
 1.00280;83.55992;121.13205;,
 -4.93832;84.22408;-18.92456;,
 -4.93428;74.61908;-19.07852;,
 -8.59524;73.95492;120.72669;,
 -8.59924;83.55992;120.88068;,
 -4.93428;74.61908;-19.07852;,
 4.66780;74.61908;-18.82708;,
 1.00684;73.95492;120.97816;,
 -8.59524;73.95492;120.72669;,
 4.66376;84.22408;-18.67312;,
 4.66780;74.61908;-18.82708;,
 1.00684;73.95492;120.97816;,
 1.00280;83.55992;121.13205;,
 4.66780;24.32492;-18.82708;,
 4.66376;33.92992;-18.67312;,
 1.00280;33.26576;121.13205;,
 1.00684;23.66076;120.97816;,
 4.66376;33.92992;-18.67312;,
 -4.93832;33.92992;-18.92456;,
 -8.59924;33.26576;120.88068;,
 1.00280;33.26576;121.13205;,
 -4.93832;33.92992;-18.92456;,
 -4.93428;24.32492;-19.07852;,
 -8.59524;23.66076;120.72669;,
 -8.59924;33.26576;120.88068;,
 -4.93428;24.32492;-19.07852;,
 4.66780;24.32492;-18.82708;,
 1.00684;23.66076;120.97816;,
 -8.59524;23.66076;120.72669;,
 4.66376;33.92992;-18.67312;,
 4.66780;24.32492;-18.82708;,
 1.00684;23.66076;120.97816;,
 1.00280;33.26576;121.13205;,
 7.34012;65.99428;-120.88073;,
 7.33612;75.59924;-120.72676;,
 3.67520;74.93512;19.07856;,
 3.67920;65.33012;18.92464;,
 7.33612;75.59924;-120.72676;,
 -2.26596;75.59924;-120.97824;,
 -5.92688;74.93512;18.82712;,
 3.67520;74.93512;19.07856;,
 -2.26596;75.59924;-120.97824;,
 -2.26192;65.99428;-121.13217;,
 -5.92284;65.33012;18.67316;,
 -5.92688;74.93512;18.82712;,
 -2.26192;65.99428;-121.13217;,
 7.34012;65.99428;-120.88073;,
 3.67920;65.33012;18.92464;,
 -5.92284;65.33012;18.67316;,
 7.33612;75.59924;-120.72676;,
 7.34012;65.99428;-120.88073;,
 3.67920;65.33012;18.92464;,
 3.67520;74.93512;19.07856;,
 7.34012;16.07992;-120.88073;,
 7.33612;25.68488;-120.72676;,
 3.67520;25.02076;19.07856;,
 3.67920;15.41576;18.92464;,
 7.33612;25.68488;-120.72676;,
 -2.26596;25.68488;-120.97824;,
 -5.92688;25.02076;18.82712;,
 3.67520;25.02076;19.07856;,
 -2.26596;25.68488;-120.97824;,
 -2.26192;16.07992;-121.13217;,
 -5.92284;15.41576;18.67316;,
 -5.92688;25.02076;18.82712;,
 -2.26192;16.07992;-121.13217;,
 7.34012;16.07992;-120.88073;,
 3.67920;15.41576;18.92464;,
 -5.92284;15.41576;18.67316;,
 7.33612;25.68488;-120.72676;,
 7.34012;16.07992;-120.88073;,
 3.67920;15.41576;18.92464;,
 3.67520;25.02076;19.07856;,
 3.87224;111.70260;98.80152;,
 3.50124;111.70260;112.96980;,
 3.50124;-0.59800;112.96980;,
 3.87224;-0.59800;98.80152;,
 3.50124;111.70260;112.96980;,
 -10.66708;111.70260;112.59876;,
 -10.66708;-0.59800;112.59876;,
 3.50124;-0.59800;112.96980;,
 -10.66708;111.70260;112.59876;,
 -10.29604;111.70260;98.43056;,
 -10.29604;-0.59800;98.43056;,
 -10.66708;-0.59800;112.59876;,
 -10.29604;111.70260;98.43056;,
 3.87224;111.70260;98.80152;,
 3.87224;-0.59800;98.80152;,
 -10.29604;-0.59800;98.43056;,
 3.50124;111.70260;112.96980;,
 3.87224;111.70260;98.80152;,
 3.87224;-0.59800;98.80152;,
 3.50124;-0.59800;112.96980;,
 9.46860;111.70260;-114.91441;,
 9.09760;111.70260;-100.74608;,
 9.09760;-0.59800;-100.74608;,
 9.46860;-0.59800;-114.91441;,
 9.09760;111.70260;-100.74608;,
 -5.07072;111.70260;-101.11712;,
 -5.07072;-0.59800;-101.11712;,
 9.09760;-0.59800;-100.74608;,
 -5.07072;111.70260;-101.11712;,
 -4.69972;111.70260;-115.28544;,
 -4.69972;-0.59800;-115.28544;,
 -5.07072;-0.59800;-101.11712;,
 -4.69972;111.70260;-115.28544;,
 9.46860;111.70260;-114.91441;,
 9.46860;-0.59800;-114.91441;,
 -4.69972;-0.59800;-115.28544;,
 9.09760;111.70260;-100.74608;,
 9.46860;111.70260;-114.91441;,
 9.46860;-0.59800;-114.91441;,
 9.09760;-0.59800;-100.74608;;
 
 42;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;92,85,96,97;,
 4;98,99,86,95;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;112,105,116,117;,
 4;118,119,106,115;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;132,125,136,137;,
 4;138,139,126,135;;
 
 MeshMaterialList {
  2;
  42;
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
  0,
  0,
  0,
  0;;
  Material {
   0.633600;0.395200;0.176000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.298400;0.298400;0.298400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  42;
  0.999657;0.000000;0.026179;,
  -0.026179;0.000000;0.999657;,
  -0.999657;0.000000;-0.026176;,
  0.026176;0.000000;-0.999657;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.999657;0.000001;0.026177;,
  -0.000124;0.999989;0.004747;,
  -0.999657;0.000001;-0.026177;,
  0.000124;-0.999989;-0.004747;,
  0.026174;0.016033;-0.999529;,
  -0.026172;-0.016030;0.999529;,
  0.999657;0.000001;0.026177;,
  -0.000124;0.999989;0.004747;,
  -0.999657;0.000001;-0.026177;,
  0.000124;-0.999989;-0.004747;,
  0.026174;0.016033;-0.999529;,
  -0.026172;-0.016030;0.999529;,
  0.999657;-0.000003;0.026177;,
  -0.000124;0.999989;0.004747;,
  -0.999657;-0.000001;-0.026177;,
  0.000124;-0.999989;-0.004747;,
  0.026176;0.016031;-0.999529;,
  -0.026176;-0.016030;0.999529;,
  0.999657;-0.000003;0.026177;,
  -0.000124;0.999989;0.004747;,
  -0.999657;-0.000001;-0.026177;,
  0.000124;-0.999989;-0.004747;,
  0.026176;0.016031;-0.999529;,
  -0.026176;-0.016030;0.999529;,
  0.999657;0.000000;0.026176;,
  -0.026179;0.000000;0.999657;,
  -0.999657;0.000000;-0.026179;,
  0.026173;0.000000;-0.999657;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.999657;0.000000;0.026176;,
  -0.026179;0.000000;0.999657;,
  -0.999657;0.000000;-0.026176;,
  0.026179;0.000000;-0.999657;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;;
  42;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;;
 }
 MeshTextureCoords {
  140;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
