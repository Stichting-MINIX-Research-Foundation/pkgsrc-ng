$NetBSD: patch-crypto_bn_bn__prime.pl,v 1.1.2.2 2014/04/08 10:09:26 tron Exp $

--- crypto/bn/bn_prime.pl.orig	2003-09-25 15:57:58.000000000 +0200
+++ crypto/bn/bn_prime.pl	2007-07-31 17:53:39.000000000 +0200
@@ -1,6 +1,8 @@
 #!/usr/local/bin/perl
 # bn_prime.pl
 
+use POSIX;
+
 $num=2048;
 $num=$ARGV[0] if ($#ARGV >= 0);
 
@@ -9,7 +11,7 @@ $p=1;
 loop: while ($#primes < $num-1)
 	{
 	$p+=2;
-	$s=int(sqrt($p));
+	$s=floor(sqrt($p));
 
 	for ($i=0; defined($primes[$i]) && $primes[$i]<=$s; $i++)
 		{
