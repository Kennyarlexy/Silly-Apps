#include "build.h"
#include "main_utilz.h"

int main()
{
    char repeat;
    do
    {
        Build build_1, build_2;
        std::cout << std::endl;
        compare_build(build_1, build_2);
        compare_reaction(build_1, build_2);
        compare_creaction(build_1, build_2);
        std::cout << "\nRetry? (y/n)" << std::endl;
        std::cin >> repeat;
    } while(repeat == 'y');

    return 0;
}