using System;

namespace Csharp {
    public class DecimalTest
    {
        public static void Main()
        {
          Console.WriteLine("#include \"s21_decimal.h\"");
          Console.WriteLine("#include <stdio.h>");
          Console.WriteLine("#include <stdlib.h>");
          Console.WriteLine("#include <math.h>");
          Console.WriteLine();
          var rand=new Random();
          float[] floatArray = new float[4];
          float zero=0;
          floatArray[1]=1/zero;
          floatArray[2]=-1/zero;
          floatArray[3]=0/zero;
          for (int iter=1;iter<=2000;iter++){
          floatArray[0]=rand.Next(3);
          Console.WriteLine("#Test Div_SpecialValue_{0}",iter);
          UInt32 s1=(UInt32)rand.Next(4);
          UInt32 s2=(UInt32)rand.Next(4);
          Console.WriteLine("s21_decimal s1 ={{{{{0},0,0,0}},{1}}};",floatArray[0],s1);
          Console.WriteLine("s21_decimal s2 ={{{{{0},0,0,0}},{1}}};",floatArray[0],s2);
          Console.WriteLine("s1=s21_div(s1,s2);");
          Console.WriteLine("float g={0}/{1};",floatArray[s1]==0? "0.0":floatArray[s1].ToString().ToUpper(),floatArray[s2]==0?"0.0":floatArray[s2].ToString().ToUpper());
          Console.WriteLine("fail_if(CheckSpecialValue(&s1, g));");
          Console.WriteLine();
          }
        }

        static decimal DecInit(){
          var rand = new Random();
          decimal s1 = new decimal(rand.Next(-2147483648,2147483647),rand.Next(-2147483648,2147483647),rand.Next(-2147483648,2147483647),Convert.ToBoolean(rand.Next(2)),(Byte)rand.Next(29));
          return s1;
        } 
        static float NextFloat()
        {
            var random=new Random();
            double mantissa = (random.NextDouble() * 2.0) - 1.0;
            // choose -149 instead of -126 to also generate subnormal floats (*)
            double exponent = Math.Pow(2.0, random.Next(-126, 128));
            return (float)(mantissa * exponent);
        }
    }
}