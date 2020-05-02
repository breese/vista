###############################################################################
#
# Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
#
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)
#
###############################################################################

find_package(AsciiDoctor QUIET)

function(vista_add_doc name source)
  get_filename_component(DESTINATION_DIR ${source} DIRECTORY)
  add_custom_target(${name} ALL
    COMMAND ${AsciiDoctor_COMMAND} -b html -D html/${DESTINATION_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${source}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endfunction()

vista_add_doc(vista-doc-vista vista.adoc)
vista_add_doc(vista-doc-rationale rationale.adoc)
include(circular/CMakeLists.txt)
include(sorted/CMakeLists.txt)

if (AsciiDoctor_FOUND)

  add_custom_target(doc
    DEPENDS vista-doc-vista
    DEPENDS vista-doc-rationale
    DEPENDS vista-doc-circular
    DEPENDS vista-doc-sorted
    )

else() # No AsciiDoctor
  add_custom_target(doc
    ${CMAKE_COMMAND} -E cmake_echo_color --red "Please install AsciiDoctor to build documentation."
    )

endif()
