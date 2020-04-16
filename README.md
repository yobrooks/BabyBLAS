# BBLAS

Driver tests all 6 functions separately using flags
It does not account for special matrices
Dot product is default test
-DDLSDRIVER --> test dls function
-DILSDRIVER --> test ils function
-DVVMDRIVER --> test vvm function
-DMVVDRIVER --> test mvv function
-DMMMDRIVER --> test mmm function