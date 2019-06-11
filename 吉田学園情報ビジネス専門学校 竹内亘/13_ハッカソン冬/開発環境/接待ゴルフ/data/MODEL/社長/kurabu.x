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
 96;
 -0.36289;8.93601;-0.10293;,
 -0.23951;8.93601;-0.40081;,
 -0.23951;-23.18622;-0.40081;,
 -0.36289;-23.18622;-0.10293;,
 0.05837;8.93601;-0.52419;,
 0.05837;-23.18622;-0.52419;,
 0.35624;8.93601;-0.40081;,
 0.35624;-23.18622;-0.40081;,
 0.47963;8.93601;-0.10293;,
 0.47963;-23.18622;-0.10293;,
 0.35624;8.93601;0.19495;,
 0.35624;-23.18622;0.19495;,
 0.05837;8.93601;0.31833;,
 0.05837;-23.18622;0.31833;,
 -0.23951;8.93601;0.19495;,
 -0.23951;-23.18622;0.19495;,
 -0.36289;8.93601;-0.10293;,
 -0.36289;-23.18622;-0.10293;,
 0.05837;8.93601;-0.10293;,
 0.05837;8.93601;-0.10293;,
 0.05837;8.93601;-0.10293;,
 0.05837;8.93601;-0.10293;,
 0.05837;8.93601;-0.10293;,
 0.05837;8.93601;-0.10293;,
 0.05837;8.93601;-0.10293;,
 0.05837;8.93601;-0.10293;,
 0.05837;-23.18622;-0.10293;,
 0.05837;-23.18622;-0.10293;,
 0.05837;-23.18622;-0.10293;,
 0.05837;-23.18622;-0.10293;,
 0.05837;-23.18622;-0.10293;,
 0.05837;-23.18622;-0.10293;,
 0.05837;-23.18622;-0.10293;,
 0.05837;-23.18622;-0.10293;,
 -0.00780;-21.59337;-2.13700;,
 -0.38129;-21.74825;-3.11680;,
 -0.60683;-21.74825;-2.13700;,
 -0.00780;-21.59337;-2.13700;,
 0.12549;-21.74825;-3.35879;,
 -0.00780;-21.59337;-2.13700;,
 0.53190;-21.74825;-2.68075;,
 -0.00780;-21.59337;-2.13700;,
 0.53190;-21.74825;-1.59325;,
 -0.00780;-21.59337;-2.13700;,
 0.12549;-21.74825;-0.91522;,
 -0.00780;-21.59337;-2.13700;,
 -0.38129;-21.74825;-1.15720;,
 -0.00780;-21.59337;-2.13700;,
 -0.60683;-21.74825;-2.13700;,
 -0.68080;-22.18222;-3.90254;,
 -1.08721;-22.18222;-2.13700;,
 0.23239;-22.18222;-4.33859;,
 0.96471;-22.18222;-3.11680;,
 0.96471;-22.18222;-1.15720;,
 0.23239;-22.18222;0.06459;,
 -0.68081;-22.18222;-0.37146;,
 -1.08721;-22.18222;-2.13700;,
 -0.84702;-22.80932;-4.33859;,
 -1.35381;-22.80932;-2.13700;,
 0.29171;-22.80932;-4.88234;,
 1.20490;-22.80932;-3.35879;,
 1.20490;-22.80932;-0.91521;,
 0.29171;-22.80932;0.60833;,
 -0.84702;-22.80932;0.06459;,
 -1.35381;-22.80932;-2.13700;,
 -0.84702;-23.50534;-4.33859;,
 -1.35381;-23.50534;-2.13700;,
 0.29171;-23.50534;-4.88234;,
 1.20490;-23.50534;-3.35879;,
 1.20490;-23.50534;-0.91521;,
 0.29171;-23.50534;0.60833;,
 -0.84702;-23.50534;0.06459;,
 -1.35381;-23.50534;-2.13700;,
 -0.68080;-24.13244;-3.90254;,
 -1.08721;-24.13244;-2.13700;,
 0.23239;-24.13244;-4.33859;,
 0.96471;-24.13244;-3.11680;,
 0.96471;-24.13244;-1.15720;,
 0.23239;-24.13244;0.06459;,
 -0.68080;-24.13244;-0.37146;,
 -1.08721;-24.13244;-2.13700;,
 -0.38129;-24.56640;-3.11680;,
 -0.60683;-24.56640;-2.13700;,
 0.12549;-24.56640;-3.35879;,
 0.53190;-24.56640;-2.68075;,
 0.53190;-24.56640;-1.59325;,
 0.12549;-24.56640;-0.91522;,
 -0.38129;-24.56640;-1.15720;,
 -0.60683;-24.56640;-2.13700;,
 -0.00780;-24.72128;-2.13700;,
 -0.00780;-24.72128;-2.13700;,
 -0.00780;-24.72128;-2.13700;,
 -0.00780;-24.72128;-2.13700;,
 -0.00780;-24.72128;-2.13700;,
 -0.00780;-24.72128;-2.13700;,
 -0.00780;-24.72128;-2.13700;;
 
 73;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 3;34,35,36;,
 3;37,38,35;,
 3;39,40,38;,
 3;41,42,40;,
 3;43,44,42;,
 3;45,46,44;,
 3;47,48,46;,
 4;36,35,49,50;,
 4;35,38,51,49;,
 4;38,40,52,51;,
 4;40,42,53,52;,
 4;42,44,54,53;,
 4;44,46,55,54;,
 4;46,48,56,55;,
 4;50,49,57,58;,
 4;49,51,59,57;,
 4;51,52,60,59;,
 4;52,53,61,60;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;58,57,65,66;,
 4;57,59,67,65;,
 4;59,60,68,67;,
 4;60,61,69,68;,
 4;61,62,70,69;,
 4;62,63,71,70;,
 4;63,64,72,71;,
 4;66,65,73,74;,
 4;65,67,75,73;,
 4;67,68,76,75;,
 4;68,69,77,76;,
 4;69,70,78,77;,
 4;70,71,79,78;,
 4;71,72,80,79;,
 4;74,73,81,82;,
 4;73,75,83,81;,
 4;75,76,84,83;,
 4;76,77,85,84;,
 4;77,78,86,85;,
 4;78,79,87,86;,
 4;79,80,88,87;,
 3;82,81,89;,
 3;81,83,90;,
 3;83,84,91;,
 3;84,85,92;,
 3;85,86,93;,
 3;86,87,94;,
 3;87,88,95;;
 
 MeshMaterialList {
  8;
  73;
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
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.664800;0.501600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.078431;0.084706;0.310588;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.009600;0.081600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.062400;0.109600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\game134\\Desktop\\nekutai.jpg";
   }
  }
  Material {
   0.034400;0.024800;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  60;
  0.000000;1.000000;0.000000;,
  -1.000000;0.000000;0.000003;,
  -0.707109;0.000000;-0.707104;,
  0.000000;0.000000;-1.000000;,
  0.707109;0.000000;-0.707104;,
  1.000000;0.000000;0.000003;,
  0.707105;0.000000;0.707109;,
  0.000000;0.000000;1.000000;,
  -0.707105;0.000000;0.707109;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  -0.472919;0.881106;-0.000000;,
  -0.305638;0.931505;-0.197190;,
  0.109996;0.961802;-0.250673;,
  0.431593;0.895848;-0.105755;,
  0.431593;0.895848;0.105755;,
  0.109996;0.961802;0.250673;,
  -0.305637;0.931505;0.197189;,
  -0.813782;0.581170;-0.000000;,
  -0.574589;0.708974;-0.408906;,
  0.210216;0.805460;-0.554115;,
  0.763522;0.614333;-0.199069;,
  0.763522;0.614333;0.199069;,
  0.210217;0.805459;0.554116;,
  -0.574588;0.708974;0.408906;,
  -0.979792;0.200021;-0.000000;,
  -0.758342;0.279811;-0.588747;,
  -0.409149;0.313694;-0.856850;,
  0.941420;0.218449;-0.256923;,
  0.941420;0.218448;0.256923;,
  0.832635;0.240103;0.499069;,
  -0.758342;0.279810;0.588747;,
  -0.979792;-0.200022;-0.000000;,
  -0.758342;-0.279811;-0.588747;,
  -0.409149;-0.313695;-0.856850;,
  0.941419;-0.218449;-0.256923;,
  0.941419;-0.218448;0.256923;,
  0.832635;-0.240103;0.499069;,
  -0.758342;-0.279811;0.588747;,
  -0.813780;-0.581174;-0.000000;,
  -0.574587;-0.708976;-0.408905;,
  -0.014407;-0.846226;-0.532629;,
  0.763520;-0.614336;-0.199068;,
  0.763520;-0.614336;0.199068;,
  0.397608;-0.806593;0.437397;,
  -0.574586;-0.708977;0.408905;,
  -0.472923;-0.881104;-0.000000;,
  -0.305640;-0.931504;-0.197191;,
  0.109997;-0.961802;-0.250675;,
  0.431596;-0.895846;-0.105756;,
  0.431596;-0.895846;0.105756;,
  0.109997;-0.961802;0.250674;,
  -0.305639;-0.931504;0.197191;,
  -0.000000;-1.000000;-0.000000;,
  0.832635;0.240104;-0.499069;,
  -0.409148;0.313694;0.856851;,
  0.832634;-0.240104;-0.499069;,
  -0.409148;-0.313694;0.856851;,
  0.758829;-0.466161;-0.454832;,
  -0.346093;-0.595721;0.724801;;
  73;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;10,12,11;,
  3;10,13,12;,
  3;10,14,13;,
  3;10,15,14;,
  3;10,16,15;,
  3;10,17,16;,
  3;10,11,17;,
  4;11,12,19,18;,
  4;12,13,20,19;,
  4;13,14,21,20;,
  4;14,15,22,21;,
  4;15,16,23,22;,
  4;16,17,24,23;,
  4;17,11,18,24;,
  4;18,19,26,25;,
  4;19,20,27,26;,
  4;20,21,28,54;,
  4;21,22,29,28;,
  4;22,23,30,29;,
  4;23,24,31,55;,
  4;24,18,25,31;,
  4;25,26,33,32;,
  4;26,27,34,33;,
  4;54,28,35,56;,
  4;28,29,36,35;,
  4;29,30,37,36;,
  4;55,31,38,57;,
  4;31,25,32,38;,
  4;32,33,40,39;,
  4;33,34,41,40;,
  4;56,35,42,58;,
  4;35,36,43,42;,
  4;36,37,44,43;,
  4;57,38,45,59;,
  4;38,32,39,45;,
  4;39,40,47,46;,
  4;40,41,48,47;,
  4;41,42,49,48;,
  4;42,43,50,49;,
  4;43,44,51,50;,
  4;44,45,52,51;,
  4;45,39,46,52;,
  3;46,47,53;,
  3;47,48,53;,
  3;48,49,53;,
  3;49,50,53;,
  3;50,51,53;,
  3;51,52,53;,
  3;52,46,53;;
 }
 MeshTextureCoords {
  96;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.071429;0.000000;,
  0.142857;0.142857;,
  0.000000;0.142857;,
  0.214286;0.000000;,
  0.285714;0.142857;,
  0.357143;0.000000;,
  0.428571;0.142857;,
  0.500000;0.000000;,
  0.571429;0.142857;,
  0.642857;0.000000;,
  0.714286;0.142857;,
  0.785714;0.000000;,
  0.857143;0.142857;,
  0.928571;0.000000;,
  1.000000;0.142857;,
  0.142857;0.285714;,
  0.000000;0.285714;,
  0.285714;0.285714;,
  0.428571;0.285714;,
  0.571429;0.285714;,
  0.714286;0.285714;,
  0.857143;0.285714;,
  1.000000;0.285714;,
  0.142857;0.428571;,
  0.000000;0.428571;,
  0.285714;0.428571;,
  0.428571;0.428571;,
  0.571429;0.428571;,
  0.714286;0.428571;,
  0.857143;0.428571;,
  1.000000;0.428571;,
  0.142857;0.571429;,
  0.000000;0.571429;,
  0.285714;0.571429;,
  0.428571;0.571429;,
  0.571429;0.571429;,
  0.714286;0.571429;,
  0.857143;0.571429;,
  1.000000;0.571429;,
  0.142857;0.714286;,
  0.000000;0.714286;,
  0.285714;0.714286;,
  0.428571;0.714286;,
  0.571429;0.714286;,
  0.714286;0.714286;,
  0.857143;0.714286;,
  1.000000;0.714286;,
  0.142857;0.857143;,
  0.000000;0.857143;,
  0.285714;0.857143;,
  0.428571;0.857143;,
  0.571429;0.857143;,
  0.714286;0.857143;,
  0.857143;0.857143;,
  1.000000;0.857143;,
  0.071429;1.000000;,
  0.214286;1.000000;,
  0.357143;1.000000;,
  0.500000;1.000000;,
  0.642857;1.000000;,
  0.785714;1.000000;,
  0.928571;1.000000;;
 }
}
