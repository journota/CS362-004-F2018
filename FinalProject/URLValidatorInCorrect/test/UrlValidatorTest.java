

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing

     // set scheme
     UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

     // set test param vars
     String urlScheme = "http://";
     String urlPort = ":80";
     String urlPath = "/";
     String urlQuery = "?action=view";
     

    // create result pairs for testUrlAuthority
     ResultPair[] testUrlAuthority = {new ResultPair ("www.oregon.com", true),
                                    new ResultPair ("oregonstate.edu", true),
                                    new ResultPair ("www.oregonstateparks", true),
                                    new ResultPair ("63.241.205.31", true),
                                    new ResultPair ("ww.ormap.net", false),
                                    new ResultPair ("www.oregon.comm", false),
                                    new ResultPair ("maps.aa", false),
                                    new ResultPair ("63.257.205.31", false),
                                    new ResultPair ("www", false),
                                    new ResultPair ("", false) };

    // set index
    int index = 0;

    // enter while loop
    while(index < testUrlAuthority.length){
        // set build string
        StringBuilder test = new StringBuilder();

        // append elements
        test.append(urlScheme);
        test.append(testUrlAuthority[index].item);
        test.append(urlPort);
        test.append(urlPath);
        test.append(urlQuery);

        // convert to string
        String testUrl = test.toString();

        // check validity
        boolean res = urlVal.isValid(testUrl);
        if(res == testUrlAuthority[index].valid){
            System.out.print(testUrl + ": expected - " + testUrlAuthority[index].valid + " actual - " + res);
        }

        // increment
        index++;
    }

    

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
