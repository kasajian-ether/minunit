// file: minunitex.h
// see http://www.jera.com/techinfo/jtns/jtn002.html
// see http://code.google.com/p/tinydom/source/browse/trunk/minunit.h

/* Example:
static const char * test_foo()
{
    mu_assert("error, foo != 7", foo == 7);
    return 0;
}

static const char * test_bar()
{
    mu_assert("error, bar != 5", bar == 5);
    return 0;
}

static const char * all_tests()
{
    mu_run_test(test_foo);
    mu_run_test(test_bar);
    return 0;
}

int main(int argc, char *argv[])
{
    const char *result = all_tests();
    if (result != 0)
    {
        printf("Failed: %s:%d\n", mu_last_test(), mu_line());
        printf("%s\n", result);
    }
    else
    {
        printf("ALL TESTS PASSED\n");
        printf("  Tests run : %d\n", mu_tests_run());
        printf("  Assertion : %d\n", mu_assertion());
    }

    return result != 0;
}
*/

#define xstr(s) str(s)
#define str(s) #s

#define INLINE_GLOBAL(type,func) inline type& func() { static type x; return x; }

INLINE_GLOBAL(int, mu_tests_run)
INLINE_GLOBAL(int, mu_assertion)
INLINE_GLOBAL(int, mu_line)
INLINE_GLOBAL(const char*, mu_last_test)

#define mu_assert(message, test)                                           \
    do                                                                     \
    {                                                                      \
        if (!(test))                                                       \
            return __FILE__ ":" xstr(__LINE__) " " message " (" #test ")"; \
        else                                                               \
            mu_assertion()++;                                              \
    } while (0)

#define mu_run_test(test)                                                  \
do                                                                         \
{                                                                          \
    const char *message;                                                   \
    mu_last_test() = #test;                                                \
    mu_line() = __LINE__;                                                  \
    message = test();                                                      \
    mu_tests_run()++;                                                      \
    if (message)                                                           \
        return message;                                                    \
} while (0)
