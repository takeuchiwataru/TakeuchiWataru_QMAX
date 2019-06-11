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
 58;
 0.20236;-0.01550;-0.00000;,
 -0.18786;1.49807;0.00000;,
 -0.18786;1.05476;1.07026;,
 -0.18786;-0.01550;1.51358;,
 -0.18786;-1.08576;1.07026;,
 -0.18786;-1.52908;0.00000;,
 -0.18786;-1.08576;-1.07026;,
 -0.18786;-0.01550;-1.51358;,
 -0.18786;1.05476;-1.07026;,
 -1.29909;2.78122;0.00000;,
 -1.29909;1.96208;1.97759;,
 -1.29909;-0.01550;2.79673;,
 -1.29909;-1.99308;1.97759;,
 -1.29909;-2.81222;0.00000;,
 -1.29909;-1.99308;-1.97759;,
 -1.29909;-0.01550;-2.79673;,
 -1.29909;1.96208;-1.97759;,
 -2.96218;3.63860;0.00000;,
 -2.96218;2.56833;2.58384;,
 -2.96218;-0.01550;3.65410;,
 -2.96218;-2.59934;2.58384;,
 -2.96218;-3.66960;0.00000;,
 -2.96218;-2.59934;-2.58384;,
 -2.96218;-0.01550;-3.65410;,
 -2.96218;2.56833;-2.58384;,
 -4.92389;3.93968;0.00000;,
 -4.92389;2.78122;2.79673;,
 -4.92389;-0.01550;3.95517;,
 -4.92389;-2.81222;2.79673;,
 -4.92389;-3.97066;0.00000;,
 -4.92389;-2.81222;-2.79673;,
 -4.92389;-0.01550;-3.95517;,
 -4.92389;2.78122;-2.79673;,
 -6.88562;3.63860;0.00000;,
 -6.88562;2.56833;2.58384;,
 -6.88562;-0.01550;3.65410;,
 -6.88562;-2.59934;2.58384;,
 -6.88562;-3.66960;0.00000;,
 -6.88562;-2.59934;-2.58384;,
 -6.88562;-0.01550;-3.65410;,
 -6.88562;2.56833;-2.58384;,
 -8.54870;2.78122;0.00000;,
 -8.54870;1.96208;1.97759;,
 -8.54870;-0.01550;2.79673;,
 -8.54870;-1.99308;1.97759;,
 -8.54870;-2.81222;0.00000;,
 -8.54870;-1.99308;-1.97759;,
 -8.54870;-0.01550;-2.79673;,
 -8.54870;1.96208;-1.97759;,
 -9.65994;1.49807;0.00000;,
 -9.65994;1.05476;1.07026;,
 -9.65994;-0.01550;1.51358;,
 -9.65994;-1.08576;1.07026;,
 -9.65994;-1.52908;0.00000;,
 -9.65994;-1.08576;-1.07026;,
 -9.65994;-0.01550;-1.51358;,
 -9.65994;1.05476;-1.07026;,
 -10.05016;-0.01550;0.00000;;
 
 64;
 3;0,1,2;,
 3;0,2,3;,
 3;0,3,4;,
 3;0,4,5;,
 3;0,5,6;,
 3;0,6,7;,
 3;0,7,8;,
 3;0,8,1;,
 4;1,9,10,2;,
 4;2,10,11,3;,
 4;3,11,12,4;,
 4;4,12,13,5;,
 4;5,13,14,6;,
 4;6,14,15,7;,
 4;7,15,16,8;,
 4;8,16,9,1;,
 4;9,17,18,10;,
 4;10,18,19,11;,
 4;11,19,20,12;,
 4;12,20,21,13;,
 4;13,21,22,14;,
 4;14,22,23,15;,
 4;15,23,24,16;,
 4;16,24,17,9;,
 4;17,25,26,18;,
 4;18,26,27,19;,
 4;19,27,28,20;,
 4;20,28,29,21;,
 4;21,29,30,22;,
 4;22,30,31,23;,
 4;23,31,32,24;,
 4;24,32,25,17;,
 4;25,33,34,26;,
 4;26,34,35,27;,
 4;27,35,36,28;,
 4;28,36,37,29;,
 4;29,37,38,30;,
 4;30,38,39,31;,
 4;31,39,40,32;,
 4;32,40,33,25;,
 4;33,41,42,34;,
 4;34,42,43,35;,
 4;35,43,44,36;,
 4;36,44,45,37;,
 4;37,45,46,38;,
 4;38,46,47,39;,
 4;39,47,48,40;,
 4;40,48,41,33;,
 4;41,49,50,42;,
 4;42,50,51,43;,
 4;43,51,52,44;,
 4;44,52,53,45;,
 4;45,53,54,46;,
 4;46,54,55,47;,
 4;47,55,56,48;,
 4;48,56,49,41;,
 3;49,57,50;,
 3;50,57,51;,
 3;51,57,52;,
 3;52,57,53;,
 3;53,57,54;,
 3;54,57,55;,
 3;55,57,56;,
 3;56,57,49;;
 
 MeshMaterialList {
  4;
  64;
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.360000;0.360000;0.360000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.120000;0.120000;0.120000;;
   0.000000;0.000000;0.000000;;
   }
  }
  Material {
   1.000000;0.569000;0.192000;1.000000;;
   5.000000;
   0.500000;0.500000;0.500000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  58;
  1.000000;0.000001;-0.000000;,
  0.887235;0.461317;0.000000;,
  0.887236;0.326201;0.326198;,
  0.887236;0.000000;0.461316;,
  0.887236;-0.326200;0.326199;,
  0.887236;-0.461316;-0.000000;,
  0.887236;-0.326200;-0.326199;,
  0.887236;0.000000;-0.461316;,
  0.887236;0.326201;-0.326198;,
  0.620393;0.784291;0.000000;,
  0.620393;0.554578;0.554577;,
  0.620392;0.000001;0.784292;,
  0.620392;-0.554579;0.554577;,
  0.620391;-0.784292;-0.000000;,
  0.620392;-0.554579;-0.554577;,
  0.620392;0.000001;-0.784292;,
  0.620393;0.554578;-0.554577;,
  0.310082;0.950710;0.000000;,
  0.310081;0.672253;0.672254;,
  0.310080;0.000000;0.950710;,
  0.310079;-0.672255;0.672253;,
  0.310079;-0.950711;0.000000;,
  0.310080;-0.672255;-0.672253;,
  0.310081;0.000000;-0.950710;,
  0.310081;0.672253;-0.672254;,
  0.000001;1.000000;0.000000;,
  0.000000;0.707106;0.707107;,
  0.000000;0.000000;1.000000;,
  0.000000;-0.707107;0.707106;,
  0.000000;-1.000000;0.000000;,
  0.000001;-0.707107;-0.707106;,
  0.000001;0.000000;-1.000000;,
  0.000001;0.707106;-0.707108;,
  -0.310081;0.950710;0.000000;,
  -0.310080;0.672253;0.672254;,
  -0.310079;0.000000;0.950711;,
  -0.310079;-0.672255;0.672253;,
  -0.310078;-0.950711;0.000000;,
  -0.310079;-0.672254;-0.672253;,
  -0.310080;0.000000;-0.950710;,
  -0.310081;0.672253;-0.672254;,
  -0.620392;0.784292;0.000000;,
  -0.620392;0.554579;0.554578;,
  -0.620391;0.000001;0.784292;,
  -0.620391;-0.554579;0.554578;,
  -0.620390;-0.784293;0.000000;,
  -0.620391;-0.554579;-0.554578;,
  -0.620391;0.000001;-0.784293;,
  -0.620391;0.554579;-0.554578;,
  -0.887234;0.461320;0.000000;,
  -0.887235;0.326203;0.326200;,
  -0.887235;0.000000;0.461318;,
  -0.887235;-0.326202;0.326201;,
  -0.887234;-0.461319;0.000000;,
  -0.887235;-0.326202;-0.326201;,
  -0.887235;0.000000;-0.461319;,
  -0.887235;0.326203;-0.326200;,
  -1.000000;0.000001;-0.000000;;
  64;
  3;0,1,2;,
  3;0,2,3;,
  3;0,3,4;,
  3;0,4,5;,
  3;0,5,6;,
  3;0,6,7;,
  3;0,7,8;,
  3;0,8,1;,
  4;1,9,10,2;,
  4;2,10,11,3;,
  4;3,11,12,4;,
  4;4,12,13,5;,
  4;5,13,14,6;,
  4;6,14,15,7;,
  4;7,15,16,8;,
  4;8,16,9,1;,
  4;9,17,18,10;,
  4;10,18,19,11;,
  4;11,19,20,12;,
  4;12,20,21,13;,
  4;13,21,22,14;,
  4;14,22,23,15;,
  4;15,23,24,16;,
  4;16,24,17,9;,
  4;17,25,26,18;,
  4;18,26,27,19;,
  4;19,27,28,20;,
  4;20,28,29,21;,
  4;21,29,30,22;,
  4;22,30,31,23;,
  4;23,31,32,24;,
  4;24,32,25,17;,
  4;25,33,34,26;,
  4;26,34,35,27;,
  4;27,35,36,28;,
  4;28,36,37,29;,
  4;29,37,38,30;,
  4;30,38,39,31;,
  4;31,39,40,32;,
  4;32,40,33,25;,
  4;33,41,42,34;,
  4;34,42,43,35;,
  4;35,43,44,36;,
  4;36,44,45,37;,
  4;37,45,46,38;,
  4;38,46,47,39;,
  4;39,47,48,40;,
  4;40,48,41,33;,
  4;41,49,50,42;,
  4;42,50,51,43;,
  4;43,51,52,44;,
  4;44,52,53,45;,
  4;45,53,54,46;,
  4;46,54,55,47;,
  4;47,55,56,48;,
  4;48,56,49,41;,
  3;49,57,50;,
  3;50,57,51;,
  3;51,57,52;,
  3;52,57,53;,
  3;53,57,54;,
  3;54,57,55;,
  3;55,57,56;,
  3;56,57,49;;
 }
 MeshTextureCoords {
  58;
  0.500000;-2.794620;,
  0.500000;-2.764510;,
  0.488740;-2.764510;,
  0.485150;-2.764510;,
  0.490140;-2.764510;,
  0.500000;-2.764510;,
  0.509860;-2.764510;,
  0.514850;-2.764510;,
  0.511260;-2.764510;,
  0.500000;-2.678780;,
  0.477980;-2.678780;,
  0.472760;-2.678780;,
  0.482730;-2.678780;,
  0.500000;-2.678780;,
  0.517270;-2.678780;,
  0.527240;-2.678780;,
  0.522020;-2.678780;,
  0.500000;-2.550460;,
  0.470110;-2.550460;,
  0.464650;-2.550460;,
  0.478220;-2.550460;,
  0.500000;-2.550460;,
  0.521780;-2.550460;,
  0.535350;-2.550460;,
  0.529890;-2.550460;,
  0.500000;-2.399110;,
  0.467210;-2.399110;,
  0.461840;-2.399110;,
  0.476710;-2.399110;,
  0.500000;-2.399110;,
  0.523290;-2.399110;,
  0.538160;-2.399110;,
  0.532790;-2.399110;,
  0.500000;-2.247750;,
  0.470110;-2.247750;,
  0.464650;-2.247750;,
  0.478220;-2.247750;,
  0.500000;-2.247750;,
  0.521780;-2.247750;,
  0.535350;-2.247750;,
  0.529890;-2.247750;,
  0.500000;-2.119430;,
  0.477980;-2.119430;,
  0.472760;-2.119430;,
  0.482730;-2.119430;,
  0.500000;-2.119430;,
  0.517270;-2.119430;,
  0.527240;-2.119430;,
  0.522020;-2.119430;,
  0.500000;-2.033700;,
  0.488740;-2.033700;,
  0.485150;-2.033700;,
  0.490140;-2.033700;,
  0.500000;-2.033700;,
  0.509860;-2.033700;,
  0.514850;-2.033700;,
  0.511260;-2.033700;,
  0.500000;-2.003590;;
 }
}
