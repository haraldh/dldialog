BEGIN {
   stackptr = 0;
   input[stackptr] = ARGV[1]; # ARGV[1] is first file
   
   for (; stackptr >= 0; stackptr--) {
      while ((getline < input[stackptr]) > 0) {
	 if (tolower($2) != "@include") {
	    print;
	    continue;
	 }
	 fpath = $3;
	 if (! (fpath in processed)) {
	    input[++stackptr] = fpath;
	 }
      }
      close(input[stackptr]);
   }
}
