/\"([^\\\"]*(\\.)?)*\"/ {  
   if ((t = index($0, "\"")) != 0) {
      u = index(substr($0, t + 1), "\"");      
      str = substr($0, t+1, u-1);
      if (length(str))
	 print "msgid \"" str "\"";
	 print "msgstr \"" str "\"\n";
   }
}
