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
 30;
 -3.74364;-0.79038;-4.05082;,
 -0.01918;0.37128;-4.58702;,
 -0.01918;-15.84136;-4.40712;,
 -3.52282;-15.84136;-4.02130;,
 3.31634;-0.79038;-4.05082;,
 3.84372;-15.84136;-4.02130;,
 3.31634;-0.79038;-4.05082;,
 4.39964;0.86488;-0.30770;,
 4.64686;-15.84136;-0.30770;,
 3.84372;-15.84136;-4.02130;,
 3.31634;-0.79038;3.43542;,
 3.84372;-15.84136;4.31394;,
 3.31634;-0.79038;3.43542;,
 -0.01918;0.37128;3.97164;,
 -0.01918;-15.84136;4.69976;,
 3.84372;-15.84136;4.31394;,
 -3.74364;-0.79038;3.43542;,
 -3.46730;-15.84136;4.31394;,
 -3.74364;-0.79038;3.43542;,
 -4.82696;0.86488;-0.30770;,
 -3.88968;-15.84136;-0.30770;,
 -3.46730;-15.84136;4.31394;,
 -3.74364;-0.79038;-4.05082;,
 -3.52282;-15.84136;-4.02130;,
 -0.01918;2.02656;-0.30770;,
 -4.82696;0.86488;-0.30770;,
 4.39964;0.86488;-0.30770;,
 -0.01918;0.37128;-4.58702;,
 -3.74364;-0.79038;-4.05082;,
 3.31634;-0.79038;-4.05082;;
 
 16;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;7,10,11,8;,
 4;12,13,14,15;,
 4;13,16,17,14;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;18,13,24,25;,
 4;13,10,26,24;,
 4;25,24,27,28;,
 4;24,26,29,27;,
 3;23,2,20;,
 3;2,5,20;,
 4;5,8,21,20;,
 4;11,14,21,8;;
 
 MeshMaterialList {
  1;
  16;
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
   0.088000;0.088000;0.414400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  22;
  -0.124309;-0.007272;-0.992217;,
  0.001476;-0.006043;-0.999981;,
  0.127237;-0.004717;-0.991861;,
  0.999570;0.027489;-0.010237;,
  0.973263;0.029382;0.227808;,
  0.001503;0.051959;0.998648;,
  -0.133495;0.050111;0.989782;,
  -0.999397;-0.034680;-0.001830;,
  0.014512;0.999895;-0.000000;,
  0.968540;0.024019;-0.247695;,
  0.136474;0.052855;0.989233;,
  -0.984194;-0.033689;0.173862;,
  -0.983519;-0.034592;-0.177466;,
  -0.268087;0.878855;0.394644;,
  0.013230;0.911613;0.410836;,
  -0.291769;0.956489;-0.000000;,
  0.293484;0.871010;0.393966;,
  0.319307;0.947651;-0.000000;,
  0.013230;0.911613;-0.410837;,
  -0.268087;0.878854;-0.394645;,
  0.293483;0.871010;-0.393967;,
  0.000000;-1.000000;0.000000;;
  16;
  4;0,1,1,0;,
  4;1,2,2,1;,
  4;9,3,3,9;,
  4;3,4,4,3;,
  4;10,5,5,10;,
  4;5,6,6,5;,
  4;11,7,7,11;,
  4;7,12,12,7;,
  4;13,14,8,15;,
  4;14,16,17,8;,
  4;15,8,18,19;,
  4;8,17,20,18;,
  3;21,21,21;,
  3;21,21,21;,
  4;21,21,21,21;,
  4;21,21,21,21;;
 }
 MeshTextureCoords {
  30;
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;;
 }
}
