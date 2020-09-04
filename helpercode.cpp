    /**
* @file parse_json.cpp
* @brief Contians functions used for parsing and retrieveing settings when the
*        API calls for it.
*/

/* --- Standard Includes --- */
#include <fstream>
#include <cstdlib>
#include <string>
#include <error.h>

/* --- RapidJson Includes --- */
#include "include/rapidjson/document.h"
#include "include/rapidjson/writer.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/ostreamwrapper.h"
#include "include/rapidjson/filereadstream.h"
#include "include/rapidjson/error/en.h"


#define SI_CONFIG_FILE "config.json"
#define JSON_MAX_READ_BUF_SIZE 65536

using namespace rapidjson;
using namespace std;

/* Declare a JSON document. JSON document parsed will be stored in this variable */
static Document config;

/*
 * @brief Parse and store JSON document into global variable
 *
 * @return int8_t 0 on SUCCESS and -1 on FAILURE
 */
int8_t loadJsonConfig()
{
    int8_t ret = -1;
    /* Open the example.json file in read mode */
    FILE *fp = fopen(SI_CONFIG_FILE, "rb");

    if (fp != NULL) {
        /* Declare read buffer */
        char readBuffer[JSON_MAX_READ_BUF_SIZE];
        /* Declare stream for reading the example stream */
        FileReadStream frstream(fp, readBuffer, sizeof(readBuffer));
        /* Parse example.json and store it in `d` */
        config.ParseStream(frstream);
        ParseResult ok = config.ParseStream(frstream);

        if (!ok) {
            fprintf(stderr, "Error Reading JSON config file: JSON parse error: %s (%u)",
                    GetParseError_En(ok.Code()), ok.Offset());
        }

        ret = 0;

    } else {
        fprintf(stderr,"Error Reading JSON config file: %s", strerror(errno));
    }

    /* Close the example.json file*/
    fclose(fp);
    return ret;
}

