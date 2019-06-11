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
 120;
 0.00000;20.00000;-10.00000;,
 7.07107;20.00000;-7.07107;,
 8.33614;15.89454;-8.33614;,
 0.00000;15.89454;-11.78908;,
 0.09055;20.00000;-0.09055;,
 0.00000;20.00000;-0.12806;,
 0.00000;15.00000;-8.00000;,
 5.65685;15.00000;-5.65685;,
 10.00000;20.00000;0.00000;,
 11.78908;15.89454;0.00000;,
 0.12806;20.00000;0.00000;,
 8.00000;15.00000;0.00000;,
 7.07107;20.00000;7.07107;,
 8.33614;15.89454;8.33614;,
 0.09055;20.00000;0.09055;,
 5.65685;15.00000;5.65685;,
 -0.00000;20.00000;10.00000;,
 -0.00000;15.89454;11.78908;,
 -0.00000;20.00000;0.12806;,
 -0.00000;15.00000;8.00000;,
 -7.07107;20.00000;7.07107;,
 -8.33614;15.89454;8.33614;,
 -0.09055;20.00000;0.09055;,
 -5.65686;15.00000;5.65685;,
 -10.00000;20.00000;-0.00000;,
 -11.78908;15.89454;-0.00000;,
 -0.12806;20.00000;-0.00000;,
 -8.00000;15.00000;-0.00000;,
 -7.07107;20.00000;-7.07107;,
 -8.33614;15.89454;-8.33614;,
 -0.09055;20.00000;-0.09055;,
 -5.65686;15.00000;-5.65685;,
 0.00000;20.00000;-10.00000;,
 0.00000;15.89454;-11.78908;,
 0.00000;20.00000;-0.12806;,
 0.00000;15.00000;-8.00000;,
 9.68159;10.00000;-9.68159;,
 0.00000;10.00000;-13.69183;,
 0.00000;10.00000;-8.00000;,
 5.65685;10.00000;-5.65685;,
 13.69183;10.00000;0.00000;,
 8.00000;10.00000;0.00000;,
 9.68159;10.00000;9.68159;,
 5.65685;10.00000;5.65685;,
 -0.00000;10.00000;13.69183;,
 -0.00000;10.00000;8.00000;,
 -9.68159;10.00000;9.68159;,
 -5.65686;10.00000;5.65685;,
 -13.69183;10.00000;-0.00000;,
 -8.00000;10.00000;-0.00000;,
 -9.68159;10.00000;-9.68159;,
 -5.65686;10.00000;-5.65685;,
 0.00000;10.00000;-13.69183;,
 0.00000;10.00000;-8.00000;,
 8.33614;4.10546;-8.33614;,
 0.00000;4.10546;-11.78908;,
 0.00000;5.00000;-8.00000;,
 5.65685;5.00000;-5.65685;,
 11.78908;4.10546;0.00000;,
 8.00000;5.00000;0.00000;,
 8.33614;4.10546;8.33614;,
 5.65685;5.00000;5.65685;,
 -0.00000;4.10546;11.78908;,
 -0.00000;5.00000;8.00000;,
 -8.33614;4.10546;8.33614;,
 -5.65686;5.00000;5.65685;,
 -11.78908;4.10546;-0.00000;,
 -8.00000;5.00000;-0.00000;,
 -8.33614;4.10546;-8.33614;,
 -5.65686;5.00000;-5.65685;,
 0.00000;4.10546;-11.78908;,
 0.00000;5.00000;-8.00000;,
 7.07107;0.00000;-7.07107;,
 0.00000;0.00000;-10.00000;,
 0.00000;0.00000;-0.08550;,
 0.06046;0.00000;-0.06046;,
 10.00000;0.00000;0.00000;,
 0.08550;0.00000;0.00000;,
 7.07107;0.00000;7.07107;,
 0.06046;0.00000;0.06046;,
 -0.00000;0.00000;10.00000;,
 -0.00000;0.00000;0.08550;,
 -7.07107;0.00000;7.07107;,
 -0.06046;0.00000;0.06046;,
 -10.00000;0.00000;-0.00000;,
 -0.08550;0.00000;-0.00000;,
 -7.07107;0.00000;-7.07107;,
 -0.06046;0.00000;-0.06046;,
 0.00000;0.00000;-10.00000;,
 0.00000;0.00000;-0.08550;,
 0.09055;20.00000;-0.09055;,
 7.07107;20.00000;-7.07107;,
 0.00000;0.00000;-10.00000;,
 7.07107;0.00000;-7.07107;,
 0.06046;0.00000;-0.06046;,
 0.00000;0.00000;-0.08550;,
 0.12806;20.00000;0.00000;,
 10.00000;20.00000;0.00000;,
 10.00000;0.00000;0.00000;,
 0.08550;0.00000;0.00000;,
 0.09055;20.00000;0.09055;,
 7.07107;20.00000;7.07107;,
 7.07107;0.00000;7.07107;,
 0.06046;0.00000;0.06046;,
 -0.00000;20.00000;0.12806;,
 -0.00000;20.00000;10.00000;,
 -0.00000;0.00000;10.00000;,
 -0.00000;0.00000;0.08550;,
 -0.09055;20.00000;0.09055;,
 -7.07107;20.00000;7.07107;,
 -7.07107;0.00000;7.07107;,
 -0.06046;0.00000;0.06046;,
 -0.12806;20.00000;-0.00000;,
 -10.00000;20.00000;-0.00000;,
 -10.00000;0.00000;-0.00000;,
 -0.08550;0.00000;-0.00000;,
 -0.09055;20.00000;-0.09055;,
 -7.07107;20.00000;-7.07107;,
 -7.07107;0.00000;-7.07107;,
 -0.06046;0.00000;-0.06046;;
 
 80;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;1,8,9,2;,
 4;10,4,7,11;,
 4;8,12,13,9;,
 4;14,10,11,15;,
 4;12,16,17,13;,
 4;18,14,15,19;,
 4;16,20,21,17;,
 4;22,18,19,23;,
 4;20,24,25,21;,
 4;26,22,23,27;,
 4;24,28,29,25;,
 4;30,26,27,31;,
 4;28,32,33,29;,
 4;34,30,31,35;,
 4;3,2,36,37;,
 4;7,6,38,39;,
 4;2,9,40,36;,
 4;11,7,39,41;,
 4;9,13,42,40;,
 4;15,11,41,43;,
 4;13,17,44,42;,
 4;19,15,43,45;,
 4;17,21,46,44;,
 4;23,19,45,47;,
 4;21,25,48,46;,
 4;27,23,47,49;,
 4;25,29,50,48;,
 4;31,27,49,51;,
 4;29,33,52,50;,
 4;35,31,51,53;,
 4;37,36,54,55;,
 4;39,38,56,57;,
 4;36,40,58,54;,
 4;41,39,57,59;,
 4;40,42,60,58;,
 4;43,41,59,61;,
 4;42,44,62,60;,
 4;45,43,61,63;,
 4;44,46,64,62;,
 4;47,45,63,65;,
 4;46,48,66,64;,
 4;49,47,65,67;,
 4;48,50,68,66;,
 4;51,49,67,69;,
 4;50,52,70,68;,
 4;53,51,69,71;,
 4;55,54,72,73;,
 4;57,56,74,75;,
 4;54,58,76,72;,
 4;59,57,75,77;,
 4;58,60,78,76;,
 4;61,59,77,79;,
 4;60,62,80,78;,
 4;63,61,79,81;,
 4;62,64,82,80;,
 4;65,63,81,83;,
 4;64,66,84,82;,
 4;67,65,83,85;,
 4;66,68,86,84;,
 4;69,67,85,87;,
 4;68,70,88,86;,
 4;71,69,87,89;,
 4;0,5,90,91;,
 4;92,93,94,95;,
 4;91,90,96,97;,
 4;93,98,99,94;,
 4;97,96,100,101;,
 4;98,102,103,99;,
 4;101,100,104,105;,
 4;102,106,107,103;,
 4;105,104,108,109;,
 4;106,110,111,107;,
 4;109,108,112,113;,
 4;110,114,115,111;,
 4;113,112,116,117;,
 4;114,118,119,115;,
 4;117,116,5,0;,
 4;118,92,95,119;;
 
 MeshMaterialList {
  2;
  80;
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
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
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
  0,
  1,
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
   1.000000;0.756863;0.364706;1.000000;;
   40.000000;
   0.180000;0.180000;0.180000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\wood000.jpg";
   }
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   59.000000;
   0.400000;0.400000;0.400000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  74;
  -0.000000;0.399496;-0.916735;,
  0.648230;0.399495;-0.648230;,
  0.916735;0.399496;0.000000;,
  0.648230;0.399496;0.648230;,
  -0.000000;0.399496;0.916735;,
  -0.648230;0.399496;0.648230;,
  -0.916735;0.399496;-0.000000;,
  -0.648230;0.399496;-0.648230;,
  -0.000000;0.353887;-0.935288;,
  0.661349;0.353887;-0.661349;,
  0.935288;0.353887;0.000000;,
  0.661349;0.353887;0.661349;,
  -0.000000;0.353887;0.935288;,
  -0.661349;0.353887;0.661349;,
  -0.935288;0.353887;-0.000000;,
  -0.661349;0.353887;-0.661349;,
  -0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;-0.000000;,
  -0.707107;0.000000;-0.707107;,
  -0.000000;-0.353887;-0.935288;,
  0.661349;-0.353887;-0.661349;,
  0.935288;-0.353887;0.000000;,
  0.661349;-0.353887;0.661349;,
  -0.000000;-0.353887;0.935288;,
  -0.661349;-0.353887;0.661349;,
  -0.935288;-0.353887;-0.000000;,
  -0.661349;-0.353887;-0.661349;,
  -0.000000;-0.399496;-0.916735;,
  0.648230;-0.399496;-0.648230;,
  0.916735;-0.399496;0.000000;,
  0.648230;-0.399496;0.648230;,
  -0.000000;-0.399496;0.916735;,
  -0.648230;-0.399496;0.648230;,
  -0.916735;-0.399496;0.000000;,
  -0.648230;-0.399496;-0.648230;,
  0.000000;-0.844118;0.536157;,
  -0.379120;-0.844118;0.379120;,
  -0.536157;-0.844118;-0.000000;,
  -0.379120;-0.844118;-0.379120;,
  0.000000;-0.844118;-0.536157;,
  0.379120;-0.844118;-0.379120;,
  0.536157;-0.844118;0.000000;,
  0.379120;-0.844118;0.379120;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  0.000000;0.495930;0.868362;,
  -0.614025;0.495930;0.614025;,
  -0.868362;0.495930;-0.000000;,
  -0.614025;0.495930;-0.614025;,
  0.000000;0.495930;-0.868362;,
  0.614025;0.495930;-0.614025;,
  0.868362;0.495930;0.000000;,
  0.614025;0.495930;0.614025;,
  0.000000;0.845423;0.534097;,
  -0.377664;0.845423;0.377664;,
  -0.534097;0.845423;-0.000000;,
  -0.377664;0.845423;-0.377664;,
  0.000000;0.845423;-0.534098;,
  0.377664;0.845423;-0.377664;,
  0.534098;0.845423;0.000000;,
  0.377664;0.845423;0.377664;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  80;
  4;0,1,9,8;,
  4;41,40,40,41;,
  4;1,2,10,9;,
  4;42,41,41,42;,
  4;2,3,11,10;,
  4;43,42,42,43;,
  4;3,4,12,11;,
  4;44,43,43,44;,
  4;4,5,13,12;,
  4;45,44,44,45;,
  4;5,6,14,13;,
  4;46,45,45,46;,
  4;6,7,15,14;,
  4;47,46,46,47;,
  4;7,0,8,15;,
  4;40,47,47,40;,
  4;8,9,17,16;,
  4;49,48,48,49;,
  4;9,10,18,17;,
  4;50,49,49,50;,
  4;10,11,19,18;,
  4;51,50,50,51;,
  4;11,12,20,19;,
  4;52,51,51,52;,
  4;12,13,21,20;,
  4;53,52,52,53;,
  4;13,14,22,21;,
  4;54,53,53,54;,
  4;14,15,23,22;,
  4;55,54,54,55;,
  4;15,8,16,23;,
  4;48,55,55,48;,
  4;16,17,25,24;,
  4;49,48,56,57;,
  4;17,18,26,25;,
  4;50,49,57,58;,
  4;18,19,27,26;,
  4;51,50,58,59;,
  4;19,20,28,27;,
  4;52,51,59,60;,
  4;20,21,29,28;,
  4;53,52,60,61;,
  4;21,22,30,29;,
  4;54,53,61,62;,
  4;22,23,31,30;,
  4;55,54,62,63;,
  4;23,16,24,31;,
  4;48,55,63,56;,
  4;24,25,33,32;,
  4;57,56,64,65;,
  4;25,26,34,33;,
  4;58,57,65,66;,
  4;26,27,35,34;,
  4;59,58,66,67;,
  4;27,28,36,35;,
  4;60,59,67,68;,
  4;28,29,37,36;,
  4;61,60,68,69;,
  4;29,30,38,37;,
  4;62,61,69,70;,
  4;30,31,39,38;,
  4;63,62,70,71;,
  4;31,24,32,39;,
  4;56,63,71,64;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;72,72,72,72;,
  4;73,73,73,73;,
  4;72,72,72,72;,
  4;73,73,73,73;;
 }
 MeshTextureCoords {
  120;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.250000;0.000000;,
  0.250000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.375000;0.000000;,
  0.375000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.000000;,
  0.500000;0.250000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.625000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.250000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  0.875000;0.000000;,
  0.875000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.250000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  1.000000;0.750000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.250000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
