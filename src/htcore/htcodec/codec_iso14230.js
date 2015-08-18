
(function() {

   var rawData;

   reset();

   return {
      feedRawData: feedRawData,
      getTest: function() {
         return rawData.length;
      }
   };


   function feedRawData(num) {
      rawData.push(num);
   };

   function reset() {
      rawData = [];
   };


})();

