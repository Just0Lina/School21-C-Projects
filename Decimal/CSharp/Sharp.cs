using System;

namespace Csharp {
    public class DecimalTest
    {
        public static void Main()
        {
            //                       bit0,bit1,bit2,sign,scale
            decimal s1 = new decimal(2147483647,0,0,Convert.ToBoolean(1),8);
            float s=NextFloat();
            // float s=0.000105028317193501f;
            decimal s2 = new decimal(s);
            printbytes(s2);
            Console.WriteLine("{0:N20} {1}",s,s2);
        //     float[] floatArray = new float[3];
        //     float zero=0;
        //   floatArray[0]=1/zero;
        //   floatArray[1]=-1/zero;
        //   floatArray[2]=0/zero;
        //   Console.WriteLine("{0}",floatArray[2].ToString().ToUpper());
            // Console.WriteLine(s1);
            // bool g=Decimal.Equals(s1,s2);

            // Console.WriteLine(NextFloat());
            // printbytes(s1);
            // Console.WriteLine(Convert.ToInt32(!g));
            // decimal s2 = new decimal(-1165043311,1897081689,1617332394,Convert.ToBoolean(0),2);
            // decimal s3=Decimal.Add(s1,s2);
            // Console.WriteLine(s1);
            // printbytes(s1);

            // Int32 g=decimal.ToInt32(s1);
            // decimal s3=Decimal.Floor(s1);
            // Console.WriteLine(s1);
            // printbytes(s1);
            // Console.WriteLine(g);
            // Console.WriteLine(s2);
        }

         static void printbytes(decimal s1)

        {
            Int32[] i; 
            string l;
            i=decimal.GetBits(s1);
            for (int j=3;j>=0;j--)
            {
                l=String.Format("{0,32}",Convert.ToString(i[j],2)).Replace(' ','0');
                if (j!=0) l+=' '; else l+='\n';
                Console.Write(l);
            }
            // for (int j=3;j>=0;j--){
            //     Console.WriteLine((UInt32)i[j]);
            // }
        }

        static float NextFloat()
        {
            // var random=new Random();
            // double mantissa = (random.NextDouble() * 2.0) - 1.0;
            // // choose -149 instead of -126 to also generate subnormal floats (*)
            // double exponent = Math.Pow(2.0, random.Next(-126, 128));
            // return (float)(mantissa * exponent);
            return 0.000105028317193501f;
        }
    }
}

















