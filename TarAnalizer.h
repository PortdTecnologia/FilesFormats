/*****************************************************************************/
/**                          TAR FILE PARSER V1.0                           **/
/** Created: 08/05/2026                            IDE: Mounriver Studio    **/
/** Autor: Gustavo Pereira da Silva                License: MIT             **/
/*****************************************************************************/

#ifndef TarAnalizer_H
#define TarAnalizer_H


/* DEPENDENCES */
#include "FlashNorSpi.h"

uint32_t oct2int(uint8_t str[], uint16_t offset){
    uint32_t ret=0;
    uint8_t dig=0;

    for(uint8_t i=0;i<12;i++){
        if(str[i+offset] == '\0' || str[i+offset] == ' ') break;
        dig = str[i+offset] - '0';
        ret=ret*8+dig;
    }
    return ret;
}


/* TAR FILES LIST - 20 FILES ->  181B in RAM */
#define  MaxFileList 20

uint8_t  T_FILES_Count=0;
uint32_t T_FILES[MaxFileList][2];
uint8_t  T_FILES_Type[MaxFileList];  // Not implemented


/* PARSER */

void TAR_Analizer(){

    uint32_t NextHeader=0; // Incremento de Header
    uint8_t BF_TEMP[256];  // Buffer Temporario de 1 Pagina

    for(uint16_t i=0;i<MaxFileList;i++){

        Nor_PageRead( ((512*NextHeader)/256), BF_TEMP );

        if(!BF_TEMP[0]){ break; }              // Se sem arquivo interromper

        T_FILES[i][0] = NextHeader;            // Salva Setor do Arquivo
        T_FILES[i][1] = oct2int(BF_TEMP, 124); // Salva Tamanho do arquivo em Bytes

        T_FILES_Count++;                       // Incrementa contador de arquivos

        NextHeader += (((T_FILES[i][1]+511)/512)+1);
    }

}


#endif

/****************************************************************/
/**         PARA MAIS INFORMACOES - MORE INFORMATIONS          **/
/**           https://www.youtube.com/@Gustavo_PORTD           **/
/**              https://x.com/gustavo_portd                   **/
/****************************************************************/