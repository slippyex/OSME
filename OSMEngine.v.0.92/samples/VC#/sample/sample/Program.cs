using System;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Windows.Forms;

namespace sample
{
    static class Program
    {
        [DllImport("kernel32")]
        public extern static int LoadLibrary(string lpLibFileName);
        [DllImport("kernel32")]
        public extern static bool FreeLibrary(int hLibModule);
        [DllImport("osmengine.dll", BestFitMapping=true)]
        public static extern int playOSMEMusicFile(string file, int trackId);
        [DllImport("osmengine.dll", BestFitMapping=true)]
        public extern static int stopOSMEMusic();

        [STAThread]
        static void Main()
        {
	    int hinstLib=LoadLibrary("osmengine.dll");
            if(hinstLib == 0) {
                Console.WriteLine("osmengine.dll not found!");
                return;
            }
            int result = 0;
            try
            {
                result = playOSMEMusicFile("gloomy.sndh", 1);
            }
            catch (Exception ex)
            {
                Console.Write(ex.Message);
                FreeLibrary(hinstLib);
                return;
            }
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
            result = stopOSMEMusic();
            FreeLibrary(hinstLib);
        }
    }
}