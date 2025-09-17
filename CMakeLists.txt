cmake_minimum_required(VERSION 3.31)
project(Rocketry_Club_Flight_Computer)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_SCAN_FOR)

# ===========================================================
# Target Definitions
# ===========================================================

add_executable(Rocketry_Club_Flight_Computer main.cpp
    SensorProcessor.cppm)

# Common libraries
# target_link_libraries(Rocketry_Club_Flight_Computer PRIVATE TBB::tbb)
# find_package(TBB REQUIRED)
#Packages

find_package(PkgConfig REQUIRED)
pkg_check_modules(libusb REQUIRED IMPORTED_TARGET libusb-1.0)
target_link_libraries(Rocketry_Club_Flight_Computer PRIVATE PkgConfig::libusb)

# CLion/Arch Linux specific: Use Ninja for faster builds
set(CMAKE_GENERATOR "Ninja" CACHE INTERNAL "Force Ninja generator")
#for raspberry pi 1
add_compile_options(--with-arch=armv6 --with-float=hard --with-fpu=vfp)

# ===========================================================
# Basic Warning Configuration (All Builds)
# ===========================================================
add_compile_options(
    -Wall                  # Enable standard warning set (memory, init, control flow)
    -Wextra                # Additional warnings (type issues, comparisons)
    -Wpedantic             # Strict ISO C++ compliance checking
    -Werror                # Treat warnings as errors for strict quality control
    -fmodules              # Use C++20 modules
    -fno-module-lazy
)

# ===========================================================
# Build Type-Specific Configurations
# ===========================================================
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    # =======================================================
    # Debug Build Settings (Development & Troubleshooting)
    # =======================================================
    message(STATUS "Configuring Debug build (CLion-friendly)")
    add_compile_options(
        -Og                  # Optimize debugging experience without breaking stepping
        -g3                  # Maximum debug information including macros
        -fno-omit-frame-pointer  # Preserve frame pointers for better stack traces
        -fno-inline          # Disable inlining for accurate call hierarchy
        -fno-optimize-sibling-calls  # Maintain call stack integrity
        -fstack-protector-strong  # Enhanced stack overflow protection

        # CLion-specific: Improve debugger performance
        -fno-var-tracking    # Reduce debug info size (faster debugging in CLion)
    )

    # Enhanced diagnostics only for debug
    add_compile_options(
        -fconcepts-diagnostics-depth=3  # Better template error messages
        -Warray-bounds=2      # Strict array bounds checking
        -Wformat-overflow=2   # Advanced printf/scanf overflow detection
        -Wstringop-overflow=4 # Aggressive string operation checking
    )

elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    # =======================================================
    # Release Build Settings (Optimized for Performance)
    # =======================================================
    message(STATUS "Configuring Release build (Arch Linux optimized)")
    add_compile_options(
        -O3                  # Maximum optimization
        -ffinite-math-only    # Assume no NaNs/Infs (safe for sudoku)
        -flto=auto            # Auto-parallelized Link-Time Optimization
        -fipa-pta             # Inter-procedural pointer analysis
        -fivopts              # Enhanced induction variable optimizations
        -fno-semantic-interposition  # Better function inlining
        -fno-plt              # Avoid PLT for faster function calls
        -march=aarch32         # Optimize for current CPU (Arch Linux advantage)
        -fhardened            # Security hardening (GCC-specific)
        -Waggressive-loop-optimizations  # Warn about questionable loop opts
        -Wvector-operation-performance   # Warn about suboptimal vector ops
    )

elseif (CMAKE_BUILD_TYPE STREQUAL "Valgrind")
    # =======================================================
    # Valgrind Sanitizer Profile (Memory Debugging)
    # =======================================================
    message(STATUS "Configuring Valgrind-friendly build")
    add_compile_options(
        -O1                  # Minimal optimizations for accurate stack traces
        -g3                  # Full debug symbols for Valgrind
        -fno-inline          # Prevent inlining for better call traces
        -fno-omit-frame-pointer  # Required for Valgrind stack analysis
        -fno-stack-protector # Avoid false positives in memory checks
        -DVALGRIND           # Optional define for code adaptations

        # Valgrind-compatible sanitizers (avoid AddressSanitizer)
        -fsanitize=undefined,leak

        # CLion integration: Improve Valgrind compatibility
        -fno-var-tracking    # Reduce debug info size
    )

    # Disable builtins that interfere with Valgrind
    add_compile_options(
        -fno-builtin-malloc
        -fno-builtin-calloc
        -fno-builtin-realloc
        -fno-builtin-free
    )

elseif (CMAKE_BUILD_TYPE STREQUAL "MinSize")
    # =======================================================
    # Embedded Size-Optimized Profile (Resource-constrained)
    # =======================================================
    message(STATUS "Configuring minimal size build")
    add_compile_options(
        -Oz                  # Aggressive size optimization
        -flto=auto           # Link-Time Optimization
        -fno-unwind-tables   # Remove exception handling tables
        -fno-asynchronous-unwind-tables  # Smaller binary size
        -fno-stack-protector # Remove stack protection overhead
        -fno-plt             # Avoid PLT for smaller binaries
        -fno-rtti            # Disable RTTI to reduce size
        -fno-exceptions      # Disable exception handling
        -ffunction-sections  # Enable linker garbage collection
        -fdata-sections      # Enable linker garbage collection

        # Size-friendly warnings
        -Wlto-type-mismatch  # Warn about type mismatches in LTO
    )

    add_link_options(
        -Wl,--gc-sections    # Remove unused code sections
        -Wl,-O1              # Linker-level optimizations
        -Wl,--relax          # Relax ELF relocation processing (size reduction)
    )

elseif (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    # =======================================================
    # Code Coverage Profile (Testing Analysis)
    # =======================================================
    message(STATUS "Configuring code coverage build")
    add_compile_options(
        -O0                  # Disable optimizations for accurate line coverage
        -g3                  # Full debug information
        --coverage           # Enable gcov instrumentation (gcov)
    )
    add_link_options(--coverage)

elseif (CMAKE_BUILD_TYPE STREQUAL "Hardened")
    # =======================================================
    # Security-Hardened Profile (Security-critical Deployment)
    # =======================================================
    message(STATUS "Configuring security-hardened build")
    add_compile_options(
        -O2                  # Balance between security and performance
        -D_FORTIFY_SOURCE=3  # Enhanced buffer overflow protection
        -fstack-protector-strong  # Stack smashing protection
        -fstack-clash-protection  # Prevent stack clash attacks
        -fcf-protection=full # Control Flow Integrity (CET)
        -fhardened           # Comprehensive security hardening
        -mspeculative-load-hardening  # Spectre mitigation
        -Wformat-overflow=2  # Advanced format string checking
        -Wstringop-overflow=4 # Strict string operation validation
    )

    add_link_options(
        -Wl,-z,relro,-z,now  # Full RELRO (Relocation Read-Only)
        -Wl,-z,noexecstack   # No executable stack
        -Wl,-z,separate-code # Separate code segments (security)
    )

elseif (CMAKE_BUILD_TYPE STREQUAL "Perf")
    # =======================================================
    # Performance Analysis Profile (Profiling/Optimization)
    # =======================================================
    message(STATUS "Configuring performance analysis build")
    add_compile_options(
        -O2                  # Good optimization level for profiling
        -g                   # Debug symbols without excessive info
        -fno-omit-frame-pointer  # Required for accurate profiling
        -fno-inline          # Prevent inlining for clear call graphs
        -DNDEBUG             # Disable assertions for realistic profiling
        -pg                  # Enable gprof profiling instrumentation
    )
    add_link_options(-pg)

endif ()

# ===========================================================
# Common Safety & Quality Settings (All Build Types)
# ===========================================================
add_compile_options(
    # Memory Safety -------------------------------------------------
    -Walloc-zero             # Warn on allocations of size zero
    -Wfree-nonheap-object    # Detect freeing non-heap memory
    -Wmismatched-new-delete  # Catch new/delete type mismatches
    -Wdangling-pointer       # Identify pointers to destroyed objects
    -Winit-self              # Warn about self-initialization
    -Wnull-dereference       # Null pointer dereference analysis
    -Wsubobject-linkage      # Warn about issues with class member linkage

    # Type Safety --------------------------------------------------
    -Wcast-align             # Pointer cast alignment issues
    -Wcast-qual              # Qualifier removal in casts
    -Wconversion             # Implicit type conversion warnings
    -Warith-conversion       # Arithmetic value changes in conversions
    -Wold-style-cast         # Detect C-style casts
    -Wzero-as-null-pointer-constant  # Require nullptr instead of 0/NULL
    -Wuseless-cast           # Redundant cast operations
    -Wstrict-aliasing=2      # Aggressive type aliasing checks

    # Code Quality -------------------------------------------------
    -Wduplicated-branches    # Identical if/else branches
    -Wduplicated-cond        # Repeated conditions
    -Wlogical-op             # Suspicious logical operator usage
    -Wshadow                 # Variable shadowing
    -Wtautological-compare   # Always-true/false comparisons
    -Wextra-semi             # Unnecessary semicolons
    -Wredundant-decls        # Multiple declarations
    -Woverloaded-virtual     # Virtual function hiding

    # Modern C++ Features ------------------------------------------
    -Wsuggest-override       # Missing override specifier
    -Wsuggest-final-types    # Classes that could be final
    -Wsuggest-final-methods  # Methods that could be final
    -Wctad-maybe-unsupported # CTAD issues
    -Wnoexcept-type          # Mismatched noexcept specifications
    -Winvalid-constexpr      # Invalid constexpr functions
    -Wpessimizing-move       # Counterproductive std::move usage

    # Error Handling -----------------------------------------------
    -Wconditionally-supported # Conditionally-supported constructs
    -Wstrict-null-sentinel    # Strict null terminators
    -Wcatch-value             # Catching exceptions by value
    -Wformat=2                # Strict format string validation
    -Wnon-virtual-dtor        # Missing virtual destructor in base

    # Special Cases ------------------------------------------------
    -Wno-error=deprecated    # Allow deprecated features (warn only)
    -Wno-error=suggest-attribute=pure  # Don't fail on pure suggestions
    --pipe                   # Faster compilation (Arch Linux advantage)
    -fopenmp                 # OpenMP parallel processing support
    -ltbb                    # Parallelization library
    -DPARALLEL               # Parallelization flag
    # CLion-specific: Improve IDE responsiveness
    -fmessage-length=0       # Ensure full error messages in CLion
)

# ===========================================================
# Build-Specific Sanitizers (Debug/Valgrind Only)
# ===========================================================
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(
        #-fsanitize=address,undefined,leak  # Comprehensive runtime checks
    )
endif ()
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    # Enable system-specific security features
    add_compile_options(-D_GNU_SOURCE)

    # Use gold linker for faster builds
    if (UNIX AND NOT APPLE)
        add_link_options(-fuse-ld=mold)
    endif ()
endif ()