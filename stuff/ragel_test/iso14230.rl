%%{
   machine iso14230;
   write data;
   alphtype unsigned char;
}%%

%%{
   action message_reset {
      /* TODO */
   }

   action got_fmt_with_len {
      len = fc & ~0x80;
   }

   action got_separate_len {
      len = fc;
   }

   action got_tgt {
      tgt = fc;
   }

   action got_src {
      src = fc;
   }

   action got_data_byte {
      /* TODO */
   }

   action message_received {
      /* TODO */
   }

   action message_error {
      /* TODO */
      fhold; fgoto msg_start;
   }






   action is_tgt_valid {
      (!tgt_care || fc == tgt_needed);
   }

   action is_src_valid {
      (!src_care || fc == src_needed);
   }

   action is_waiting_for_data {
      (data_received++ < len);
   }

   action is_checksum_correct {
      1/*TODO*/
   }






   fmt_with_len = (0x81..0xff);
   fmt_separate_len = (0x80 any);
   tgt = (any);
   src = (any);
   data = (any);
   checksum = (any);

   message = 
      (
         (fmt_with_len @got_fmt_with_len | fmt_separate_len @got_separate_len)
         (tgt        when is_tgt_valid          @got_tgt       )
         (src        when is_src_valid          @got_src       )
         (data       when is_waiting_for_data   @got_data_byte )*
         <:
         (checksum   when is_checksum_correct   @message_received)
      ) >to(message_reset) $err(message_error)
      ;

   main := (msg_start: message)*;

   # Initialize and execute.
   write init;
   write exec;
}%%



