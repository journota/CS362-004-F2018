

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
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	 //Expected valid URLs
	   assertTrue(urlVal.isValid("http://www.google.com"));
	   assertTrue(urlVal.isValid("http://www.google.com/"));
	 //FAIL assertTrue(urlVal.isValid("ftp://foo.bar.com/"));
	   assertTrue(urlVal.isValid("http://go.au"));
	   assertTrue(urlVal.isValid("http://go.co.uk"));
	   //FAIL assertTrue(urlVal.isValid("https://commons.apache.org"));
	   assertTrue(urlVal.isValid("http://255.255.255.255"));
	   
	 //Expected invalid URLs
	   assertFalse(urlVal.isValid(""));
	   assertFalse(urlVal.isValid("http/www.google.com"));
	   // FAIL assertFalse(urlVal.isValid("zzzhttp://www.google.com"));
	   // FAIL assertFalse(urlVal.isValid("http://256.256.256.256"));
	   
	   assertTrue(urlVal.isValid("FEDC:BA98:7654:3210:FEDC:BA98:7654:3210")); //address from RFC2732
	   
	   
	   String[] schemes = {"http"};
	   UrlValidator urlVal2 = new UrlValidator(schemes,0);
	   assertTrue(urlVal2.isValid("http://www.google.com"));
	   
	   
   }
   
   
   public void testYourFirstPartition()
   {
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
	        boolean res = urlVal.isValidScheme(testUrl);
//	        assertEquals(testUrlAuthority[index].valid,res);
	        System.out.print(testUrl + ": expected - " + testUrlAuthority[index].valid + " actual - " + res + "\n");

	        // increment
	        index++;
	    }
    

   }
   
   public void testYourSecondPartition(){
	// set scheme
	     UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	     // set test param vars
	     String urlAuthority = "www.google.com";
	     String urlPort = ":80";
	     String urlPath = "/";
	     String urlQuery = "?action=view";
	     

	    // create result pairs for testUrlAuthority
	     ResultPair[] testUrlScheme = {new ResultPair ("http://", true),
	                                    new ResultPair ("h3t://", true),
	                                    new ResultPair ("ftp://", true),
	                                    new ResultPair ("http//", false),
	                                    new ResultPair ("http:", false),
	                                    new ResultPair ("http:/", false),
	                                    new ResultPair (":http://", false),
	                                    new ResultPair ("htt://", false),
	                                    new ResultPair ("://", false),
	                                    new ResultPair ("", false) };

	    // set index
	    int index = 0;

	    // enter while loop
	    while(index < testUrlScheme.length){
	        // set build string
	        StringBuilder test = new StringBuilder();

	        // append elements
	        test.append(testUrlScheme[index].item);
	        test.append(urlAuthority);
	        test.append(urlPort);
	        test.append(urlPath);
	        test.append(urlQuery);

	        // convert to string
	        String testUrl = test.toString();

	        // check validity
	        boolean res = urlVal.isValidScheme(testUrl);
//	        assertEquals(testUrlScheme[index].valid,res);
	        System.out.print(testUrl + ": expected - " + testUrlScheme[index].valid + " actual - " + res + "\n");

	        // increment
	        index++;
	    }

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing
	   int numTests = 100;    //specify number of tests for loop

	    String[] invalidUrls = new String[numTests]; //hold the invalid urls
	    int c = 0;	//counter for invalid urls
	
	    //valid url parts
	    String[] scheme = {"http://", "", "https://","ftp://"}; //4
	    String[] authority = {"www.google.com", "go.com", "go.au", "0.0.0.0"}; //4
	    String[] port = {":80", ":65535", ""}; //3
	    String[] path = {"/test1", "/test1/file", "/$23", ""}; //4
	    String[] query = {"?action=view", "?action=edit&mode=up", ""}; //3


	    //loop based on number of tests defined above
	    //use random part selection from each of the arrays
	    for(int i = 0; i < numTests; i++) {
	      int schemeRand = (int) (Math.random() * 4);
	      int authorityRand = (int) (Math.random() * 4);
	      int portRand = (int) (Math.random() * 3);
	      int pathRand = (int) (Math.random() * 4);
	      int queryRand = (int) (Math.random() *3);

	      //url builder
	      String testUrl = scheme[schemeRand] + authority[authorityRand] + port[portRand] + path[pathRand] + query[queryRand];
	      UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	      //check if url returned valid
	      boolean valid = validator.isValid(testUrl);

	      //if url is invalid, log the url
	      if(valid == false) {
	        invalidUrls[c] = testUrl;
	        c++;
	      }
	    }
	    //print logged invalid urls
	    System.out.println("Results for Invalid URLs:\n");
	    for (int j = 0; j < invalidUrls.length; j++) {
	      if(invalidUrls[j] != null){
	    	System.out.println(invalidUrls[j]);
	      }
	    } 
	  }
}
   



