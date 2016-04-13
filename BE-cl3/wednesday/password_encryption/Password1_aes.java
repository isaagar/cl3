
import java.security.Key;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.Scanner;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;
import sun.misc.*;



public class Password1 {
	
	private static final String ALGO = "AES";
	//key of size 16 bytes
	//private static byte[] keyValue = new byte[]{'t','h','y','u','e','f','z','s','y','k','f','l','d','a','b','m'};
	
	public static Key key1(String otp) {
		String str = otp.concat(otp);
		str = str.concat(str);
		//System.out.println("Present Key value  : "+str);
		byte[] keyValue = str.getBytes();
		//System.out.println("Key value Before Hash : " +keyValue);
		SecretKeySpec key = null;
		try {
			key = new SecretKeySpec(keyValue, ALGO);
			//System.out.println("Key : "+key);

		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return key;
		
	}
	
	
	
	//method used for encryption accepts the data and the key 
	public static String encrypt(String Data, Key key) throws Exception {
		//Key key = generateKey();
		//System.out.println("in encrypt");
		Cipher c = Cipher.getInstance(ALGO);
		//c set to encrypt mode
		c.init(Cipher.ENCRYPT_MODE, key);
		byte[] encVal = c.doFinal(Data.getBytes("UTF-8"));
		String encrypted = new BASE64Encoder().encode(encVal);
		
		return encrypted;
		
	}
	//method for decrypting using the same key
	public static String decrypt(String encrypted, Key key) throws Exception {
		//Key key = generateKey();
		Cipher c = Cipher.getInstance(ALGO);
		//c set to decrypt mode
		c.init(Cipher.DECRYPT_MODE, key);
		//Byte bencrypted = Byte.valueOf(encrypted);
		byte[] decoded = new BASE64Decoder().decodeBuffer(encrypted);
		
		byte[] decValue = c.doFinal(decoded);
		String decrypted = new String(decValue);
		return decrypted;
		
	}
	
	
	
	
}