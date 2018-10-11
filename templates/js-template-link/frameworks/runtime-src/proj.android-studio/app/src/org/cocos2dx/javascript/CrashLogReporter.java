package org.cocos2dx.javascript;


import android.os.Environment;
import android.provider.Settings;
import android.util.Log;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;



public class CrashLogReporter
{
    private static String log_file = null;
    private static String log_file_name = null;

    public static String server_url = "http://1_en_dol.oasmobile.com:60000/crash_log/index.php";
    private static String log_file_prefix = "android";


    public static void setCrashLogReporterUrl(String url)
    {
        if (null == url || url.equals("")) return ;

        server_url = url;
    }


    public static void setLogFilePrefix(String prefix)
    {
        if (null == prefix || prefix.equals("")) return ;

        log_file_prefix = prefix;
    }


    public static void UploadLog()
    {
        AppActivity.GetInstance().runOnUiThread(new Runnable() {
            @Override
            public void run()
            {
                ExecuteUploadLog();
            }
        });
    }


    private static void ExecuteUploadLog()
    {
        try
        {
            SaveLog();
            new CrashLogUploadTask().execute(log_file, log_file_name);
        }
        catch(Exception e)
        {
            e.printStackTrace();
            Log.e("CRASH_LOG_REPORTER", "Exception " + e.toString());
            //Toast.makeText(AppActivity.GetInstance().getApplicationContext(), e.toString(), Toast.LENGTH_LONG).show();
        }


        /* clear log
        try {
            Runtime.getRuntime().exec("logcat -c");
        }
        catch (Exception e)
        {
            e.printStackTrace();
            Toast.makeText(app.getApplicationContext(), e.toString(), Toast.LENGTH_LONG).show();
        }//*/
    }


    private static void SaveLog() throws Exception
    {
        // TODO 临时用这个ID
        String android_id = Settings.Secure.getString(AppActivity.GetInstance().getContentResolver(),
                Settings.Secure.ANDROID_ID);

        Date date = new Date();
        SimpleDateFormat df = new SimpleDateFormat("yyyy_MM_dd_HH_mm_ss", Locale.US);
        String file_name = log_file_prefix;
        if (android_id != null) file_name += "_" + android_id;
        file_name += "_" + df.format(date);
        file_name += "_" + date.getTime();
        file_name += ".log";

        File file = new File (Environment.getExternalStorageDirectory(), file_name);
        log_file = file.getAbsolutePath();
        log_file_name = file_name;
        Log.i("CRASH_LOG_REPORTER", "LOG FILE(SAVING) " + log_file);

        if(file.exists()) file.delete();


        //write log to file
        int pid = android.os.Process.myPid();

        String command = String.format("logcat -d -v threadtime *:*");
        Process process = Runtime.getRuntime().exec(command);

        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        StringBuilder result = new StringBuilder();
        String currentLine = null;

        while ((currentLine = reader.readLine()) != null)
        {
            if (currentLine != null && currentLine.contains(String.valueOf(pid)))
            {
                result.append(currentLine);
                result.append("\n");
            }
        }

        FileWriter out = new FileWriter(file);
        out.write(result.toString());
        out.close();

        Log.i("CRASH_LOG_REPORTER", "LOG FILE(SAVED) " + log_file);

        /*
        Toast.makeText(AppActivity.GetInstance().getApplicationContext(),
                "Log(saved) -> " + log_file,
                Toast.LENGTH_LONG).show();//*/
    }
}
