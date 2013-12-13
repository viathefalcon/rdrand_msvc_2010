Using Intel’s Secure Key (RDRAND) in MS Visual C++ 2010:

Among the features added to Intel’s 3rd-Generation Core i* processors is a Digital Random Number Generator (DRNG) backed by an on-die hardware entropy source. This new hardware feature is made available to software via the also-new RDRAND instruction.

If you’re still using the compiler which shipped with Visual C++ 2010, it seems the only way to leverage the DRNG is either via a third-party library (the one available from Intel’s website was, as of writing, broken) or by dipping into assembly programming. Of these the latter comes with a couple of catches: the mnenomic/intrinsic for the instruction is not available for older assemblers/compilers, and the assembly is slightly different for 32- and 64-bit environments.

This project demonstrates testing whether the host processor supports the RDRAND instruction as well as invoking it (via assembly). When built for 32-bit CPUs, the assembly is inlined; when built for 64-bit CPUs, the assembly is linked in via an exernal module (the 64-bit compiler in Visual Studio 2010 does not support inline assembly).

For the most part, the project simply follows the Software Implementation Guide from Intel. Additionally, it demonstrates invoking the instruction via its opcode, and linking a module implemented in assembly into a VC++ project.
