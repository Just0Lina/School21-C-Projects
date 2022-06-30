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
          // Console.WriteLine("{0}",floatArray[2].ToString().ToUpper());
          for (int iter=1;iter<=10;iter++){
          // floatArray[0]=rand.Next(3);
          Console.WriteLine("#Test Div_{0}",iter);
          float s=NextFloat();
          decimal s1=0;//, s2=DecInit();
          Int32[] i=decimal.GetBits(s1);
          Console.WriteLine("s21_decimal s1 ={{{{{0},{1},{2},{3}}},0}};    // {4} {5} {6}",i[0],i[1],i[2],i[3],i[3]>>31,i[3]<<8>>24,s1);
          // s1=new decimal(s);
          // UInt32 s1=(UInt32)rand.Next(4);
          // UInt32 s2=(UInt32)rand.Next(4);
          // Console.WriteLine("s21_decimal s1 ={{{{{0},0,0,0}},{1}}};",floatArray[0],s1);
          // Console.WriteLine("s21_decimal s2 ={{{{{0},0,0,0}},{1}}};",floatArray[0],s2);
          // float f=floatArray[s1]*floatArray[s2];
          // float s=NextFloat();
          decimal s2=new decimal(Math.Abs(s)<1e-28?0.0:s);
          // s2=s;
          // i=Decimal.GetBits(s2);
          // Console.WriteLine("s21_decimal s2 ={{{{{0},{1},{2},{3}}},0}};    // {4} {5} {6}",i[0],i[1],i[2],i[3],i[3]>>31,i[3]<<8>>24,s2);
          // bool ans=Decimal.Equals(s1,s2);
          Console.WriteLine("float g={0};",Math.Abs(s)<1e-28?0.0:s);
          Console.WriteLine("s21_from_float_to_decimal(g,&s1);");
          // s1=s1/s2;
          i=Decimal.GetBits(s2);
          Console.WriteLine("s21_decimal answer ={{{{{0},{1},{2},{3}}},0}};    // {4} {5} {6}",i[0],i[1],i[2],i[3],i[3]>>31,i[3]<<8>>24,s1);
          // Console.WriteLine("s21_from_decimal_to_float(s1,&ans);");
          // Console.WriteLine("if (g!=s) printf(\"%f %f Test {0}\\n\",g,s);",iter);
          Console.WriteLine("fail_if(s21_is_equal(s1,answer));");
          // Console.WriteLine("fail_if(CheckSpecialValue(&s1, {0}));",f.ToString().ToUpper());
          Console.WriteLine();
          
          // i=Decimal.GetBits(s1);
          // Console.WriteLine("int g = 0;");
          // Console.WriteLine("//{0} {1}",s1,i[0]);
          // Int32 g=Decimal.ToInt32(s1);
          // i=decimal.GetBits(s1);
          // Console.WriteLine("s21_decimal answer ={{{{{0},{1},{2},{3}}},0}};    // {4} {5} {6}",i[0],i[1],i[2],i[3],i[3]>>31,i[3]<<8>>24,s1); 
          }
        }

        static decimal DecInit(){
          var rand = new Random();
          decimal s1 = new decimal(rand.Next(-2147483648,2147483647),rand.Next(-2147483648,2147483647),rand.Next(-2147483648,2147483647),Convert.ToBoolean(rand.Next(2)),(Byte)rand.Next(20,28));
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