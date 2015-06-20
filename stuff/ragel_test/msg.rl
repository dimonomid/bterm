%%{
   machine my_machine;
   write data;
   alphtype unsigned char;
}%%

%%{
   action message_reset {
      /* TODO */
      data_received = 0;
   }

   action got_len {
      len = fc;
   }

   action got_data_byte {
      /* TODO */
   }

   action message_received {
      /* TODO */
   }

   action is_waiting_for_data {
      (data_received++ < len);
   }

   action is_checksum_correct {
      1/*TODO*/
   }


   len = (any);
   fmt_separate_len = (0x80 any);
   data = (any);
   checksum = (any);

   message = 
      (
         # first byte: length of the data
         (len                                   @got_len)
         # user data
         (data       when is_waiting_for_data   @got_data_byte )*
         # place higher priority on the previous machine (i.e. data)
         <: 
         # last byte: checksum
         (checksum   when is_checksum_correct   @message_received)
      ) >to(message_reset)
      ;

   main := (msg_start: message)*;

   # Initialize and execute.
   write init;
   write exec;
}%%



