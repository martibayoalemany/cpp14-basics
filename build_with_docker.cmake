cmake_minimum_required(VERSION 3.5)

set(build_dir ${CMAKE_CURRENT_LIST_DIR}/bin)

if(NOT EXISTS ${build_dir})
	  file(MAKE_DIRECTORY ${build_dir})
endif()

SET(DOCKER_RUN_CMD 
	docker run -it cpp14-basics:latest 
)
execute_process(
  COMMAND ${DOCKER_RUN_CMD} bash -c "${CMAKE_COMMAND} .."
)

execute_process(
  COMMAND ${DOCKER_RUN_CMD} bash -c "${CMAKE_COMMAND} --build ."
  WORKING_DIRECTORY ${build_dir}
)

execute_process(
  COMMAND ${DOCKER_RUN_CMD} bash -c "ctest -VV"
  WORKING_DIRECTORY ${build_dir}
  RESULT_VARIABLE test_result
)


if(${test_result})
  message(FATAL_ERROR "test failed")
endif()

