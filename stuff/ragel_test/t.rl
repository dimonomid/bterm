%%{
	machine test1;
	write data;
   alphtype unsigned char;
}%%

%%{
   action got_fmt_with_len {
      len = fc & ~0x80;
   }

   action got_separate_len {
      len = fc;
   }

   fmt_with_len = (0x81..0xff);
   fmt_separate_len = (0x80 any);
   tgt = (any);
   src = (any);

   main := 
      ( fmt_with_len @got_fmt_with_len | fmt_separate_len @got_separate_len) (tgt src)
      ;

   # Initialize and execute.
   write init;
   write exec;
}%%

