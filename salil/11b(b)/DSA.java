import java.math.BigInteger; 
import java.security.MessageDigest; 
import java.security.NoSuchAlgorithmException; 
import java.util.Random; 
import java.util.logging.Level; 
import java.util.logging.Logger; 
 
public class DSA { 
int primeCenterie = 20; 
BigInteger q; 
BigInteger p; 
BigInteger g; 
BigInteger y; 
BigInteger x; BigInteger k; 
 
Random rand = new Random(); 
 
DSA() {} 
 
 
//*****public key and private key generation*****// 
 
public void generateKey() { 
 
//Choose a prime number q 
q = new BigInteger(160, primeCenterie, rand);
 
 
//Choose another prime number p, such that p­1 mod q = 0. 
p = generateP(q, 512);
 
//Choose an integer g, such that 1 < g < p, g^q mod p = 1 and //g = h^((p–1)/q) mod p. 
g = generateG(p, q);
 
do { 
 
//Choose private key x, such that 0 < x < q. 
x = new BigInteger(q.bitCount(), rand);
 
} while (x.compareTo(BigInteger.ZERO) != 1 && x.compareTo(q) != ­1); 
 
//Compute public key y as g^x mod p. 
y = g.modPow(x, p);
 
} 
 
private BigInteger generateP(BigInteger q, int l) { 
 
if (l % 64 != 0) { 
throw new IllegalArgumentException("L value is wrong"); 
} 
 
BigInteger pTemp; 
BigInteger pTemp2; 
 
do { 
 
pTemp = new BigInteger(l, primeCenterie, rand); 
pTemp2 = pTemp.subtract(BigInteger.ONE); pTemp = pTemp.subtract(pTemp2.remainder(q)); 
} while (!pTemp.isProbablePrime(primeCenterie) || pTemp.bitLength() != l); 
 
return pTemp; 
 
} 
 
private BigInteger generateG(BigInteger p, BigInteger q) { 
 
BigInteger aux = p.subtract(BigInteger.ONE); 
BigInteger pow = aux.divide(q); 
BigInteger gTemp; 
 
do { 
 
gTemp = new BigInteger(aux.bitLength(), rand); 
} while (gTemp.compareTo(aux) != ­1 && gTemp.compareTo(BigInteger.ONE) != 1); 
 
return gTemp.modPow(pow, p); 
 
} 
 
//***** Generating signature*****// 
 
//Generate a random number k, such that 0 < k < q. 
public BigInteger generateK(BigInteger q) {
 
BigInteger tempK; 
 
do {
 
tempK = new BigInteger(q.bitLength(), rand); 
} while (tempK.compareTo(q) != ­1 && tempK.compareTo(BigInteger.ZERO) != 1); 
 
return tempK; 
 
} 
 
//Compute r as (g^k mod p) mod q. 
public BigInteger generateR() {
 
k = generateK(q); 
BigInteger r = g.modPow(k, p).mod(q); 
 
return r; 
 } 
 
public BigInteger generateS(BigInteger r, byte[] data) 
{ 
 
MessageDigest md; 
BigInteger s = BigInteger.ONE; 
 
try { 
 
//Generate message digest h. 
md = MessageDigest.getInstance("SHA­1");
 
md.update(data); 
BigInteger hash = new BigInteger(md.digest());
 
 
//Compute s = i*(h+r*x) mod q where i is such that k*i mod q = //1.
s = (k.modInverse(q).multiply(hash.add(x.multiply(r)))).mod(q); 
 
} catch (NoSuchAlgorithmException ex) { 
Logger.getLogger(DSA.class.getName()).log(Level.SEVERE, null, ex); 
 
} 
 
return s; 
 
} 
 
boolean verify(byte[] data, BigInteger r, BigInteger s) { 
 
 if (r.compareTo(BigInteger.ZERO) <= 0 || r.compareTo(q) >= 0) { 
 
 return false; 
 
 } 
 
 if (s.compareTo(BigInteger.ZERO) <= 0 || s.compareTo(q) >= 0) { 
 
 return false; 
 
 } 
 
 MessageDigest md; 
 
 BigInteger v = BigInteger.ZERO; 
 
  try { 
 
 md = MessageDigest.getInstance("SHA­1"); 
 
 md.update(data); 
 
 BigInteger hash = new BigInteger(md.digest()); 
 
 BigInteger w = s.modInverse(q); 
 
 BigInteger u1 = hash.multiply(w).mod(q); 
 
 BigInteger u2 = r.multiply(w).mod(q); 
 
 v = ((g.modPow(u1, p).multiply(y.modPow(u2, p))).mod(p)).mod(q); 
 
 } catch (NoSuchAlgorithmException ex) { 
 
 Logger.getLogger(DSA.class.getName()).log(Level.SEVERE, null, ex); 
 
 } 
 
 return v.compareTo(r) == 0; 
 
} 
 
public static void main(String args[]) 
{ 
 
DSA d = ​
new​
 DSA(); 
System.​
out ​
.println(​
"Generating parameter tuple..\n"​
); 
d.generateKey();
//By generating p,q,g for x,y 
BigInteger r=d.generateR();
//Generate r 
System.​
out ​
.println(​
"Enter data:\n"​
); 
Scanner reader=​
new​
 Scanner(System.​
in ​
); 
String arr1=reader.next(); 
byte​
 [] data= arr1.getBytes(); 
//byte [] ​
arr​
={(byte) 110011,1,0}; 
BigInteger s=d.generateS(r,arr );
//Generate s 
System.​
out ​
.println(​
"Signature: "​
+r+s);
//Signature is (r,s) 
b=verify(data,r,s) 
System.​
out ​
.println(​
"Result is: "​
+b); 
 
} 
 } 
