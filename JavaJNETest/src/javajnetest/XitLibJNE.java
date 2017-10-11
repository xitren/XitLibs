/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package javajnetest;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.NativeLong;
import com.sun.jna.Platform;
import com.sun.jna.*;
/**
 *
 * @author xitre
 */
public class XitLibJNE {

//    public native int intMethod(int n);
//    public native boolean booleanMethod(boolean bool);
//    public native String stringMethod(String text);
//    public native int intArrayMethod(int[] intArray);

    
    public interface simpleDLL extends Library {
        simpleDLL INSTANCE = (simpleDLL) Native.loadLibrary(
            (Platform.isWindows() ? "libXitLibJNE" : "libXitLibJNE"), simpleDLL.class);
        int giveIntGetInt(); // char giveVoidPtrGetChar(void* param);
    }
    public static void main(String[] args)
    {
        simpleDLL sdll = simpleDLL.INSTANCE;

        sdll.giveIntGetInt();  // call of void function
//        System.loadLibrary("msvcrt"); 
//        System.loadLibrary("msvcp_win"); 
//        System.loadLibrary("KERNEL32"); 
//        try{
//            String path = System.getProperty("java.library.path");
//            System.out.println(path);
//            System.loadLibrary("ntdll"); 
//            System.loadLibrary("KERNEL32"); 
//            System.loadLibrary("KERNELBASE"); 
//            System.loadLibrary("TmUmEvt64"); 
//            System.loadLibrary("ADVAPI32"); 
//            System.loadLibrary("PSAPI"); 
//            System.loadLibrary("SHLWAPI"); 
//            System.loadLibrary("msvcrt"); 
//            System.loadLibrary("sechost"); 
//            System.loadLibrary("ucrtbase"); 
//            System.loadLibrary("bcryptPrimitives"); 
//            System.loadLibrary("RPCRT4"); 
//            System.loadLibrary("USER32"); 
//            System.loadLibrary("win32u");
//            System.loadLibrary("GDI32"); 
//            System.loadLibrary("gdi32full"); 
//            System.loadLibrary("msvcp_win"); 
//            System.loadLibrary("USER32"); 
//            System.loadLibrary("win32u"); 
//            System.loadLibrary("VERSION"); 
//            System.loadLibrary("tmmon64"); 
//            System.loadLibrary("IMM32"); 
//            System.loadLibrary("cygwin1"); 
//            System.loadLibrary("libXitLibJNE");
////            Runtime.getRuntime().load("C:\\Users\\xitre\\Documents\\Projects\\XitLibs\\XitLibJNE\\dist\\Debug\\MinGW-Windows\\libXitLibJNE.dll");
////System.load("C:\\Users\\xitre\\Documents\\Projects\\XitLibs\\XitLibJNE\\dist\\Debug\\MinGW-Windows\\libXitLibJNE.dll");
////            
//        System.out.println("Loaded CallApi");
//        }catch(UnsatisfiedLinkError e){
//            e.printStackTrace();
//        }
//        XitLibJNE sample = new XitLibJNE();
//        int     square = sample.intMethod(5);
//        boolean bool   = sample.booleanMethod(true);
//        String  text   = sample.stringMethod("JAVA");
//        int     sum    = sample.intArrayMethod( new int[]{1,1,2,3,5,8,13} );
//
//        System.out.println("intMethod: " + square);
//        System.out.println("booleanMethod: " + bool);
//        System.out.println("stringMethod: " + text);
//        System.out.println("intArrayMethod: " + sum);
    }
    
}
