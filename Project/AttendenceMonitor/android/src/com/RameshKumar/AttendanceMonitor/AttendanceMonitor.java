package com.RameshKumar.AttendanceMonitor;

import java.lang.String;
import java.io.File;
import java.io.FileInputStream;
import java.io.OutputStream;
import java.io.InputStream;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.lang.Exception;
import java.util.ArrayList;
import java.nio.charset.StandardCharsets;

public class AttendanceMonitor
{
   static String getData()
   {
     try {
       File destinationFile =
       new File("/storage/emulated/0/AttendanceMonitor/studentAttendanceData.txt");
       if(!destinationFile.exists())return "[]";
         else
         {
            InputStream out = new FileInputStream(destinationFile);
            byte[] data = new byte[(int) destinationFile.length()];
            out.read(data);
            out.close();
            String result = new String(data, StandardCharsets.UTF_8);
            return result;
         }}
       catch(Exception e){ e.printStackTrace(); return "[]"; }
   }

   static void updateData(String jsonObject)
   {
     if(jsonObject.equals(""))return;
     try {
       File path = new File("/storage/emulated/0/AttendanceMonitor");
       if(!path.exists())path.mkdirs();
       File destinationFile = new File(path.getPath()+"/studentAttendanceData.txt");
       OutputStream out = new FileOutputStream(destinationFile);
       byte [] byteTemp = jsonObject.getBytes();
       out.write(byteTemp);
       out.close();
      }
    catch(Exception e){ e.printStackTrace(); }
   }
}

