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
 28;
 -0.51560;0.16328;-0.15269;,
 -0.32311;0.27546;0.88217;,
 -0.29943;2.71759;1.31848;,
 -1.15074;2.66783;0.14525;,
 -1.18612;0.09922;-1.55579;,
 -1.15586;2.53961;-1.17575;,
 -0.64232;2.42437;-4.62948;,
 -0.75988;-0.01603;-5.00952;,
 -0.01414;2.36493;-4.85784;,
 -0.05269;-0.05345;-5.23787;,
 0.61508;2.43700;-4.35296;,
 0.58483;-0.00340;-4.73299;,
 1.05861;2.60722;-0.85123;,
 1.08152;0.00983;-1.34252;,
 0.97812;2.66085;0.20262;,
 0.80192;0.22372;-0.12703;,
 0.14169;2.75215;1.30131;,
 0.07772;0.31380;0.93006;,
 0.17158;2.53961;-1.17575;,
 -0.31840;2.53961;-1.17575;,
 -0.44047;3.14211;0.39824;,
 0.01641;3.14009;-0.61502;,
 -0.04191;3.16467;0.78977;,
 0.37388;3.12698;-0.01009;,
 0.02346;4.13717;-0.29722;,
 0.41186;4.11794;-0.07041;,
 -0.42675;4.12971;0.33616;,
 0.00275;4.14616;0.64696;;
 
 24;
 4;0,1,2,3;,
 4;4,0,3,5;,
 4;5,6,7,4;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,2,1,17;,
 3;12,18,14;,
 3;19,5,3;,
 4;19,8,6,5;,
 4;10,8,18,12;,
 3;8,19,18;,
 4;3,20,21,19;,
 4;2,22,20,3;,
 4;14,23,22,16;,
 4;18,21,23,14;,
 3;2,16,22;,
 3;21,18,19;,
 4;21,24,25,23;,
 4;20,26,24,21;,
 4;22,27,26,20;,
 4;23,25,27,22;;
 
 MeshMaterialList {
  9;
  24;
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  7;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.350000;0.350000;0.350000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "22679000120.jpg";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "thDW0G3HBL.jpg";
   }
  }
  Material {
   0.568400;0.568400;0.568400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.467200;0.006400;0.028000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.710000;0.710000;0.710000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
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
   TextureFilename {
    "fox_up.jpg";
   }
  }
 }
 MeshNormals {
  34;
  -0.903802;0.147888;0.401585;,
  -0.597547;0.537463;0.595039;,
  -0.895214;-0.184780;0.405522;,
  -0.930985;-0.171409;0.322312;,
  -0.997228;-0.053947;0.051236;,
  -0.989343;0.051203;-0.136301;,
  0.171177;0.153096;-0.973273;,
  0.865396;0.073011;-0.495741;,
  0.999773;-0.018919;0.009800;,
  0.913564;0.358838;0.191404;,
  0.919036;-0.094375;0.382709;,
  0.435462;-0.161825;0.885542;,
  0.122722;0.949772;-0.287876;,
  -0.105113;0.958283;-0.265793;,
  -0.765397;0.623482;-0.159494;,
  -0.539776;0.589296;-0.601142;,
  -0.449276;0.591296;0.669716;,
  0.887332;0.448437;-0.107453;,
  0.703707;0.042520;-0.709217;,
  -0.865730;0.056016;-0.497367;,
  -0.644846;0.096854;0.758151;,
  -0.310069;0.156852;-0.937686;,
  -0.025113;-0.163306;0.986256;,
  -0.063059;0.996831;-0.048498;,
  -0.055869;0.996922;-0.054999;,
  0.019889;0.997563;-0.066871;,
  -0.277840;0.934756;-0.221441;,
  -0.010174;0.999058;-0.042185;,
  0.039753;0.998523;-0.037046;,
  -0.070243;0.996646;-0.041992;,
  0.791465;0.429936;0.434440;,
  0.277900;0.818601;0.502657;,
  0.728238;0.339390;-0.595385;,
  0.878318;0.011725;0.477934;;
  24;
  4;3,2,1,0;,
  4;4,3,0,4;,
  4;4,5,5,4;,
  4;21,6,6,21;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,10,8;,
  4;9,11,11,10;,
  4;11,22,22,11;,
  3;23,12,24;,
  3;13,25,26;,
  4;13,27,28,25;,
  4;29,27,12,23;,
  3;27,13,12;,
  4;26,14,15,13;,
  4;1,16,14,0;,
  4;9,17,30,31;,
  4;12,32,17,9;,
  3;1,31,16;,
  3;15,12,13;,
  4;32,18,18,17;,
  4;14,19,19,15;,
  4;16,20,20,20;,
  4;17,33,33,30;;
 }
 MeshTextureCoords {
  28;
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
