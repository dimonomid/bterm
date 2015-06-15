%%{
	machine test1;
	write data;
   alphtype unsigned char;
}%%

%%{
   action got_byte {
   }

   action got_fmt_with_len {
      len = fc & ~0x80;
      fgoto mylabel;
   }

   action got_separate_len {
      len = fc;
   }

   action test_err {
      fhold; fgoto mylabel;
   }

   fmt_with_len = (0x81..0xff);
   fmt_separate_len = (0x80 any);
   tgt = (any);
   src = (any);

   main := 
            (
             ( 'arg' @err(test_err)  'b' -> mylabel) ('c' (mylabel: 'd'))
            )
      ;

   # Initialize and execute.
   write init;
   write exec;
}%%


