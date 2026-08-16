cmake_minimum_required(VERSION 3.10)
project(PlacementMatch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(placement_checker
    main.cpp
    src/models/student.cpp
    src/models/company.cpp
    src/models/application.cpp
    src/services/registration.cpp
    src/services/companyregistration.cpp
    src/services/eligibilitychecker.cpp
    src/services/search.cpp
    src/services/csvutils.cpp
    src/services/csvstorage.cpp
    src/services/applicationsystem.cpp
    src/strategies/eligibilitystrategy.cpp
    src/utils/trie.cpp
    src/utils/logger.cpp
    src/utils/config.cpp
)

# Unit tests as a separate executable
add_executable(run_tests
    tests/test_main.cpp
    src/models/student.cpp
    src/models/company.cpp
    src/services/eligibilitychecker.cpp
)

# Integration tests as a separate executable
add_executable(run_integration_tests
    tests/test_integration.cpp
    src/models/student.cpp
    src/models/company.cpp
    src/models/application.cpp
    src/services/eligibilitychecker.cpp
    src/services/applicationsystem.cpp
)