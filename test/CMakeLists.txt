
function(add_test_program program_name)
    add_executable(${program_name} ${program_name}.c)
    target_link_libraries(${program_name} libcuckoo)
    add_test(NAME ${program_name} COMMAND ${program_name})
endfunction(add_test_program)

function(add_test_program_static program_name)
    add_executable(${program_name}-static ${program_name}.c)
    target_link_libraries(${program_name}-static libcuckoo-static)
    add_test(NAME ${program_name}-static COMMAND ${program_name}-static)
endfunction(add_test_program_static)

add_test_program(main)
add_test_program_static(main)
