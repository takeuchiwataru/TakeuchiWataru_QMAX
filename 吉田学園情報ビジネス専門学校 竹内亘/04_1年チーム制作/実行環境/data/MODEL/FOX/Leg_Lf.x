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
 44;
 5.02138;9.48816;6.95322;,
 2.78301;12.48217;7.07920;,
 2.33749;11.48419;10.82419;,
 2.18322;8.49017;14.56848;,
 2.31725;8.73966;1.08519;,
 2.42102;12.10795;4.45727;,
 4.42004;5.12185;2.83168;,
 2.18373;4.96966;-0.80308;,
 4.26332;1.00507;1.95625;,
 2.01897;0.51133;-2.28903;,
 4.08704;-3.48600;1.58007;,
 1.87496;-3.11387;-2.40676;,
 4.35847;-7.47805;5.19912;,
 1.71053;-6.98758;-1.38511;,
 3.54460;-11.96911;4.69810;,
 1.49735;-11.87415;0.52698;,
 1.97706;3.99911;17.43827;,
 4.33769;4.87235;10.69690;,
 1.80616;-0.24247;17.56156;,
 4.16605;0.75556;11.44447;,
 1.61906;-5.60677;14.56328;,
 3.97819;-4.48400;9.07046;,
 1.54218;-8.10181;12.06544;,
 1.43266;-11.47010;9.31758;,
 5.39022;4.99711;6.20249;,
 5.03879;-3.98501;5.32526;,
 5.52464;0.50605;5.95114;,
 0.05251;-8.04928;12.06767;,
 -0.04064;-11.46672;9.31883;,
 0.09122;-5.50405;14.56654;,
 0.23216;-0.11668;17.56532;,
 0.36753;4.19515;17.44349;,
 0.56250;8.73448;14.57465;,
 1.06473;11.57636;10.74669;,
 1.52299;12.55915;7.01758;,
 1.16468;12.13080;4.43664;,
 1.01434;8.75632;1.05695;,
 0.83194;5.00607;-0.81873;,
 0.68208;0.57615;-2.23278;,
 0.61783;-3.01404;-2.31202;,
 0.51347;-6.84284;-1.29738;,
 0.25501;-11.82439;0.64827;,
 -1.64650;-12.01311;4.85415;,
 0.02364;-0.79537;6.46964;;
 
 44;
 4;0,1,2,3;,
 4;1,0,4,5;,
 4;4,0,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;0,3,16,17;,
 4;17,16,18,19;,
 4;19,18,20,21;,
 4;21,20,22,12;,
 4;12,22,23,14;,
 3;0,17,24;,
 3;6,0,24;,
 3;21,12,25;,
 3;25,12,10;,
 4;19,21,25,26;,
 4;26,25,10,8;,
 4;24,17,19,26;,
 4;24,26,8,6;,
 4;23,22,27,28;,
 4;22,20,29,27;,
 4;20,18,30,29;,
 4;18,16,31,30;,
 4;16,3,32,31;,
 4;2,33,32,3;,
 4;2,1,34,33;,
 4;1,5,35,34;,
 4;5,4,36,35;,
 4;4,7,37,36;,
 4;7,9,38,37;,
 4;9,11,39,38;,
 4;11,13,40,39;,
 4;13,15,41,40;,
 4;15,14,42,41;,
 4;23,28,42,14;,
 4;35,43,33,34;,
 4;43,35,36,37;,
 4;33,43,31,32;,
 4;31,43,29,30;,
 4;43,37,38,39;,
 4;29,43,28,27;,
 4;28,43,41,42;,
 4;41,43,39,40;;
 
 MeshMaterialList {
  9;
  44;
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
  61;
  0.501917;0.864441;0.028663;,
  0.344687;0.831233;0.436168;,
  0.543289;0.574506;0.612193;,
  0.957376;0.287270;-0.030116;,
  0.331236;0.831502;-0.445968;,
  0.484408;0.547398;-0.682425;,
  0.912674;0.131782;-0.386858;,
  0.493577;0.320896;-0.808336;,
  0.921150;0.023331;-0.388507;,
  0.870687;0.047879;-0.489502;,
  0.923430;-0.112287;-0.366973;,
  0.880946;-0.116317;-0.458699;,
  0.971080;-0.237044;-0.028516;,
  0.886804;-0.187261;-0.422507;,
  0.974994;-0.221727;-0.014960;,
  0.899779;-0.150201;-0.409679;,
  0.932778;0.083032;0.350759;,
  0.954942;0.054429;0.291760;,
  0.933713;-0.103307;0.342792;,
  0.952409;-0.084888;0.292764;,
  0.905115;-0.266698;0.331118;,
  0.932181;-0.217789;0.289147;,
  0.888403;-0.293354;0.353105;,
  0.887797;-0.256319;0.382252;,
  0.998221;0.054481;-0.024205;,
  0.989711;-0.142474;-0.013200;,
  0.999157;-0.035082;-0.021308;,
  -0.022848;-0.667114;0.744605;,
  -0.003307;-0.875661;0.482915;,
  -0.034557;-0.600233;0.799078;,
  -0.014577;-0.237338;0.971318;,
  0.042102;0.290939;0.955815;,
  0.074042;0.670437;0.738263;,
  0.061374;0.893422;0.445006;,
  0.048150;0.997446;0.052757;,
  0.036032;0.889907;-0.454717;,
  0.024390;0.584348;-0.811136;,
  0.010566;0.379528;-0.925120;,
  -0.029964;0.171454;-0.984736;,
  -0.077463;-0.112245;-0.990657;,
  -0.102524;-0.304829;-0.946873;,
  -0.108010;-0.357480;-0.927654;,
  -0.005882;-0.998843;0.047727;,
  -0.997709;0.062746;-0.025295;,
  -0.016553;-0.999615;-0.022276;,
  -0.995401;0.094588;-0.015178;,
  -0.995627;0.093319;-0.004221;,
  -0.993721;0.110987;0.014162;,
  -0.995953;0.078083;-0.044500;,
  -0.996705;0.057671;-0.057046;,
  -0.998753;0.049847;-0.002645;,
  -0.996883;0.075590;-0.022602;,
  -0.999739;0.015970;0.016347;,
  -0.999561;0.024050;0.017314;,
  -0.996883;0.037226;-0.069559;,
  -0.997067;0.026002;-0.071978;,
  -0.996697;0.080425;-0.011248;,
  -0.999851;0.007889;0.015379;,
  -0.994891;0.083841;-0.056240;,
  -0.987583;0.152480;-0.037807;,
  -0.997120;0.014774;-0.074387;;
  44;
  4;3,0,1,2;,
  4;0,3,5,4;,
  4;5,3,6,7;,
  4;7,6,8,9;,
  4;9,8,10,11;,
  4;11,10,12,13;,
  4;13,12,14,15;,
  4;3,2,16,17;,
  4;17,16,18,19;,
  4;19,18,20,21;,
  4;21,20,22,12;,
  4;12,22,23,14;,
  3;3,17,24;,
  3;6,3,24;,
  3;21,12,25;,
  3;25,12,10;,
  4;19,21,25,26;,
  4;26,25,10,8;,
  4;24,17,19,26;,
  4;24,26,8,6;,
  4;28,27,27,28;,
  4;27,29,29,27;,
  4;29,30,30,29;,
  4;30,31,31,30;,
  4;31,2,32,31;,
  4;1,33,32,2;,
  4;1,0,34,33;,
  4;0,4,35,34;,
  4;4,5,36,35;,
  4;5,7,37,36;,
  4;7,38,38,37;,
  4;38,39,39,38;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;44,42,42,44;,
  4;28,28,42,42;,
  4;45,43,46,47;,
  4;43,45,48,49;,
  4;46,43,50,51;,
  4;50,43,52,53;,
  4;43,49,54,55;,
  4;52,43,56,57;,
  4;56,43,58,59;,
  4;58,43,55,60;;
 }
 MeshTextureCoords {
  44;
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
