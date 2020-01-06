NAME EMPSTEST
ROWS
 N  OBJ
 E  VLRES   
 E  RAI72   
 G  DEP73   
 E  DEP72   
 E  TRS72   
 G  INV72   
COLUMNS
    RVAD72    OBJ       1
    RVAD72    RAI72     1
    RVAD73    OBJ       1
    RVAD73    RAI72     1.101
    DEPN72    DEP72     -1.101
    DEPN72    DEP73     1
    DEPN73    RAI72     -1.101
    DEPN73    TRS72     1
    INVT72    INV72     -1
    INVT72    TRS72     -1
    WK1T78    INV72     -1
    WK1T78    TRS72     -1
    WK2T78    INV72     -2
    WK2T78    TRS72     -1
    WK3T78    INV72     -3
    WK3T78    TRS72     -1
    MPS_RgVLRES  VLRES     1
    MPS_RgRAI72  RAI72     1
    MPS_RgDEP72  DEP72     1
RHS
    RHS1      VLRES     2.34
    RHS1      RAI72     -1.234
    RHS1      TRS72     5.67
    RHS1      INV72     -2
BOUNDS
 FR BND1      RVAD72  
 UP BND1      DEPN72    1.51985
 FX BND1      DEPN73    8.07907
 FX BND1      INVT72    8.07907
 UP BND1      WK1T78    8.07907
 FR BND1      WK2T78  
 LO BND1      WK3T78    1.57957
 UP BND1      MPS_RgVLRES  2.34
 UP BND1      MPS_RgRAI72  34
 UP BND1      MPS_RgDEP72  2.34
ENDATA
