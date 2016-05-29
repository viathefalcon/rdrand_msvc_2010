using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace RdRandPInvoke
{
    class Program
    {
        static void Main(string[] args)
        {
            if (rdrand_supported())
            {
                Console.WriteLine("Usage: {0} [number of random numbers to generate]", System.AppDomain.CurrentDomain.FriendlyName);
                UInt32 iterations = (args.Length > 0) ? UInt32.Parse(args[0]) : 32;

                for (UInt32 u = 0; u < iterations; u++)
                {
                    UInt32 value = 0;
                    if (rdrand_next(ref value))
                    {
                        Console.WriteLine("RDRAND returned: {0}", value);
                    }
                    else
                    {
                        Console.WriteLine("RDRAND did not return a value.");
                    }
                }

                for (UInt32 bound = iterations, u = 0; u < bound; u++)
                {
                    UInt32 r = rdrand_uniform(bound);
                    if (r >= bound)
                    {
                        Console.WriteLine("{0}) Generated a value ({1}) equal to or greater than the bound ({2})!?", u, r, bound);
                        break;
                    }
                    Console.WriteLine("{0}) Generated {1} with bound of {2}", u, r, bound);
                }
            }
            else
            {
                Console.WriteLine("RDRAND is not supported on this host.");
            }
        }

        [DllImport("RdRandLib.dll")]
        private static extern bool rdrand_supported();

        [DllImport("RdRandLib.dll")]
        private static extern bool rdrand_next(ref UInt32 value);

        [DllImport("RdRandLib.dll")]
        private static extern UInt32 rdrand_uniform(UInt32 bound);
    }
}
