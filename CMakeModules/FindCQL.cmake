FIND_PATH ( CQL_INCLUDE_DIR NAMES cql PATHS /usr/include/ /usr/local/include/ )
FIND_LIBRARY ( CQL_LIBRARY NAMES cql PATHS /usr/lib /usr/local/lib ) 


IF ( CQL_INCLUDE_DIR AND CQL_LIBRARY )
    SET ( CQL_FOUND TRUE )
ENDIF (  )


IF ( CQL_FOUND )
    MESSAGE ( STATUS "Found DataStax C++ Driver for Apache Cassandra headers in ${CQL_INCLUDE_DIR}" )
    MESSAGE ( STATUS "Found DataStax C++ Driver for Apache Cassandra library: ${CQL_LIBRARY}" )
ELSE (  )
    IF ( CQL_FIND_REQUIRED )
        MESSAGE ( FATAL_ERROR "Could not find DataStax C++ Driver for Apache Cassandra" )
    ENDIF (  )
ENDIF (  )


