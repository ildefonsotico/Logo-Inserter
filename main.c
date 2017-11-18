
#include "USB/usb.h"
#include "USB/usb_host_msd.h"
#include "USB/usb_host_msd_scsi.h"
#include "MDD File System/FSIO.h"
#include "stdio.h"



#define PLL_96MHZ_OFF   0xFFFF
#define PLL_96MHZ_ON    0xF7FF

_CONFIG2(FNOSC_PRIPLL & POSCMOD_HS & PLL_96MHZ_ON & PLLDIV_DIV2) // Primary HS OSC with PLL, USBPLL /2
_CONFIG1(JTAGEN_OFF & FWDTEN_OFF & ICS_PGx2)   // JTAG off, watchdog timer off
  


FSFILE * myFile, * arq;
BYTE Bufferdados[32];
char receivebuffer[50];
size_t numBytes;
SearchRec rec;
volatile BOOL deviceAttached;
typedef struct 
{
   BYTE comprimentoID;
   BYTE mapaCor;
   BYTE tipoImagem;
   short int x_origin;
   short int y_origin;
   unsigned short int  largura;
   unsigned short int  altura;
   BYTE  profundidadePixel;
   BYTE  imageDescriptor;
} HEADER;

typedef struct {
   unsigned char r,g,b,a;
} PIXEL;
HEADER header;
PIXEL pixel;
int main(void)
{   unsigned char atributo;
    unsigned char size = 0, i;
    deviceAttached = FALSE;
    

    //Initialize the stack
    USBInitialize(0);
  
    while(1)
    {
        //USB stack process function
        USBTasks();

        //if thumbdrive is plugged in
        if(USBHostMSDSCSIMediaDetect())
        {
            deviceAttached = TRUE;

            //now a device is attached
            //See if the device is attached and in the right format
            if(FSInit())
            {
                //Opening a file in mode "w" will create the file if it doesn't
                //  exist.  If the file does exist it will delete the old file
                //  and create a new one that is blank.
atributo = ATTR_ARCHIVE | ATTR_READ_ONLY | ATTR_HIDDEN  ;
int resul;
resul=FindFirst ("logo.TGA", atributo, &rec);
if (resul == 0)
{
/*	myFile = FSfopen(rec.filename,"r");
	FSfread(receivebuffer, 4, 1, myFile);
	arq = FSfopen("Leitura.txt", "w");
	FSfwrite(receivebuffer,1,4,arq);
	
	FSfread(receivebuffer, 4, 1, myFile);
	FSfwrite(receivebuffer,1,4,arq);
	FSfread(receivebuffer, 5, 1, myFile);
	FSfwrite(receivebuffer,1,5,arq);
	FSfclose(myFile);
	FSfclose(arq);
	*/
	myFile = FSfopen(rec.filename,"r");
	FSfread(Bufferdados, 18, 1, myFile);
	header.comprimentoID=Bufferdados [0];
	header.mapaCor=Bufferdados[1];
	if(header.mapaCor != 0)
	{
		arq = FSfopen("Mapacor.txt","w");
		FSfwrite("Diferente de Zero",1,17,arq);
		FSfclose(arq);
		
	}
	else
	{
		arq = FSfopen("Mapacor.txt","w");
		FSfwrite("Igual a zero",1,12,arq);
		FSfclose(arq);
	}
	

	
	header.tipoImagem=Bufferdados[2];
	
		if(header.tipoImagem == 0)
	{
		arq = FSfopen("tipoIma.txt","w");
		FSfwrite("Igual a zero",1,12,arq);
		FSfclose(arq);
		
	}
	else if(header.tipoImagem == 0x01)
	{
		arq = FSfopen("TipoIma.txt","w");
		FSfwrite("Igual a um",1,10,arq);
		FSfclose(arq);
	}
	else if(header.tipoImagem == 0x02)
	{
		arq = FSfopen("TipoIma.txt","w");
		FSfwrite("Igual a dois",1,12,arq);
		FSfclose(arq);
	}
	else if(header.tipoImagem == 0x03)
	{
		arq = FSfopen("TipoIma.txt","w");
		FSfwrite("Igual a tres",1,12,arq);
		FSfclose(arq);
	}
	else if(header.tipoImagem == 0x04)
	{
		arq = FSfopen("TipoIma.txt","w");
		FSfwrite("Igual a quatro",1,14,arq);
		FSfclose(arq);
	}
	else 
	{
		arq = FSfopen("TipoIma.txt","w");
		FSfwrite("Diferente",1,9,arq);
		FSfclose(arq);
	}
    short int conversao[3];
    conversao[0] = Bufferdados[8]; 
    conversao[0] = conversao[0]<<8;
    conversao[0] = (conversao[0] | Bufferdados[9]);    
	header.x_origin=conversao[0];
	conversao[1] = Bufferdados[10];
	conversao[1] = conversao[1]<<8;
    conversao[1] = (conversao[1] | Bufferdados[11]);
    header.y_origin = conversao[1]; 
    
    conversao[2] = Bufferdados[12];
	conversao[2] = conversao[2]<<8;
	short int jj = Bufferdados[13];
    conversao[2] = (conversao[2] | jj);
    //header.largura = conversao[2];
    //header.largura = header.altura;
    
    /*resul=FindFirst ("largura.txt", atributo, &rec); 
    
    arq = FSfopen(rec.filename,"r");
	FSfread(Bufferdados, 1, 1, arq);
	FSfclose(arq);
	Bufferdados[0]+=3;
	if(Bufferdados[0] == 54)
	{
		arq = FSfopen("asc.txt","w");
		FSfwrite("Valor 6",1,7,arq);
		FSfclose(arq);
	}
		if(Bufferdados[0] == 57)
	{
		arq = FSfopen("asc.txt","w");
		//FSfwrite("Valor 9",1,7,arq);
		//FSfwrite("   ",1,3,arq);
		FSfwrite((char *)Bufferdados,1,2,arq);
		
		FSfclose(arq);
	}
	else if(Bufferdados[0] != 0)
	{
		arq = FSfopen("asc.txt","w");
		FSfwrite("Diferente zero",1,14,arq);
		FSfclose(arq);
	}
	else
	{
		arq = FSfopen("asc.txt","w");
		FSfwrite("nao sei",1,9,arq);
		FSfclose(arq);
	}
    
    */
	
    conversao[3] = Bufferdados[14];
	conversao[3] = conversao[3]<<8;
	short int ja = Bufferdados[15];
    conversao[3] = (conversao[3] | ja);
    header.altura = conversao[3];
    
    header.largura = header.altura;
    short int ori;
    BYTE parse[5];
    BYTE llvv = 0xf1, ls = 15;
    unsigned short int conv, ys;
    ys = llvv;
    if(ys == 241)
	{
		arq = FSfopen("asc2.txt","w");
		FSfwrite("Valor *241*",1,11,arq);
		FSfclose(arq);
	}
    conv = ys << 8;
    if(conv == 61696)
	{
		arq = FSfopen("asc.txt","w");
		FSfwrite("Valor 61696",1,11,arq);
		FSfclose(arq);
	}
	else if(conv == 0)
	{
		arq = FSfopen("asc.txt","w");
		FSfwrite("Valor zero!",1,11,arq);
		FSfclose(arq);
	}
	else
	{
		arq = FSfopen("asc.txt","w");
		FSfwrite("Valor error",1,11,arq);
		FSfclose(arq);
	}
    conv = (conv | ls); 
    

    parse[0] = (conv % 10);
    parse[0] = parse[0] + 48;
    ori = (conv /10);
    arq = FSfopen("largura.txt", "w");
	//FSfwrite((char *)parse,1,4,arq);
	parse[1] = (ori % 10);
	parse[1] = parse[1] + 48;
	ori = (ori / 10);
    //FSfwrite((char *)parse,1,4,arq);
    parse[2] = (ori % 10);
    parse[2] = parse[2] + 48;
	ori = (ori / 10);
	parse[3] = (ori % 10);
    parse[3] = parse[3] + 48;
	ori = (ori / 10);
	parse[4] = (ori % 10);
    parse[4] = parse[4] + 48;
	ori = (ori / 10);
	//char * test = "658";
    FSfwrite((char *)parse,1,5,arq);
    //FSfwrite(test,1,3,arq);
    FSfclose(arq);
    
    
    
    header.profundidadePixel = Bufferdados[16];
    header.imageDescriptor = Bufferdados[17];
    arq = FSfopen("Header.rtf", "w");
	FSfwrite((char *)header.comprimentoID,1,1,arq);
	//header.y_origin=Bufferdados[
	FSfwrite(header.mapaCor,1,1,arq);
	FSfwrite(header.tipoImagem,1,1,arq);
	FSfclose(arq);
	FSfclose(myFile);
	
}
else
{
	myFile = FSfopen("Error.txt","w");
	FSfwrite("Nao Leu tga",1,19,myFile);
	FSfclose(myFile);
}
/*int resul;
resul=FindFirst ("*.TGA", atributo, &rec);
if (resul == 0)
{
	char * nome = rec.filename;
	myFile = FSfopen("leutga.txt","w");
	FSfwrite(nome,1,10,myFile);
	int res;
	FSfclose(myFile);
	res = FindNext(&rec);
	int  asc = 0x30;
	myFile = FSfopen("leutga2.txt","w");
	while(res == 0)
	{
	
		char * nome2 = rec.filename;
		BOOL flag = TRUE;
		int cont = 0;
		while(flag)
		{
			if(&nome2 != "\0")
			{
				nome2 ++;
				cont ++;
			}
			else
			{
				flag = FALSE;
			}
			
		}
		 		//char * atribut = rec.attributes;
    	//int  size = rec.filesize;
		//FSfwrite(asc, 1, 1, myFile);
		//FSfwrite("\n", 1,2,myFile);
		FSfwrite(nome2,1,cont,myFile);
		//FSfwrite(atribut,1,10,myFile);
		//FSfwrite(size,1,5,myFile);
		//FSwrite("\0", 1, 2, myFile);
		
		//asc = asc+1;
		res = FindNext(&rec);
	}
	FSfclose(myFile);
		
	
	
}
else
{
	myFile = FSfopen("Error.txt","w");
	FSfwrite("Nao Leu tga",1,19,myFile);
}
//myFile = FSfopen("test.txt","w");
//FSfwrite("Teste In pen drive",1,19,myFile);
//int pos = FSftell(myFile);
//FSfwrite(pos,1,19,myFile);
//FSfopen("testii.bmp","w");
//FSmkdir ("FOUR\\FIVE\\SIX");
               
    */           
               //FSfwrite(um,1,19,arq);

                //Always make sure to close the file so that the data gets
                //  written to the drive.
                //FSfclose(myFile);
//				FSfclose(arq);
                //Just sit here until the device is removed.
                while(deviceAttached == TRUE)
                {
                    USBTasks();
                }
            }
        }
    }
    return 0;
}


/****************************************************************************
  Function:
    BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event,
                void *data, DWORD size )

  Summary:
    This is the application event handler.  It is called when the stack has
    an event that needs to be handled by the application layer rather than
    by the client driver.

  Description:
    This is the application event handler.  It is called when the stack has
    an event that needs to be handled by the application layer rather than
    by the client driver.  If the application is able to handle the event, it
    returns TRUE.  Otherwise, it returns FALSE.

  Precondition:
    None

  Parameters:
    BYTE address    - Address of device where event occurred
    USB_EVENT event - Identifies the event that occured
    void *data      - Pointer to event-specific data
    DWORD size      - Size of the event-specific data

  Return Values:
    TRUE    - The event was handled
    FALSE   - The event was not handled

  Remarks:
    The application may also implement an event handling routine if it
    requires knowledge of events.  To do so, it must implement a routine that
    matches this function signature and define the USB_HOST_APP_EVENT_HANDLER
    macro as the name of that function.
  ***************************************************************************/

BOOL USB_ApplicationEventHandler( BYTE address, USB_EVENT event, void *data, DWORD size )
{
    switch( event )
    {
        case EVENT_VBUS_REQUEST_POWER:
            // The data pointer points to a byte that represents the amount of power
            // requested in mA, divided by two.  If the device wants too much power,
            // we reject it.
          
            return TRUE;

        case EVENT_VBUS_RELEASE_POWER:
            // Turn off Vbus power.
            // The PIC24F with the Explorer 16 cannot turn off Vbus through software.

            //This means that the device was removed
           
            deviceAttached = FALSE;
            return TRUE;
            break;

        case EVENT_HUB_ATTACH:
         
            return TRUE;
            break;

        case EVENT_UNSUPPORTED_DEVICE:
         
            return TRUE;
            break;

        case EVENT_CANNOT_ENUMERATE:
            //UART2PrintString( "\r\n***** USB Error - cannot enumerate device *****\r\n" );
         
            return TRUE;
            break;

        case EVENT_CLIENT_INIT_ERROR:
            //UART2PrintString( "\r\n***** USB Error - client driver initialization error *****\r\n" );
         
            return TRUE;
            break;

        case EVENT_OUT_OF_MEMORY:
            //UART2PrintString( "\r\n***** USB Error - out of heap memory *****\r\n" );
        
            return TRUE;
            break;

        case EVENT_UNSPECIFIED_ERROR:   // This should never be generated.
            //UART2PrintString( "\r\n***** USB Error - unspecified *****\r\n" );
          
            return TRUE;
            break;

        default:
          
            break;
    }

    return FALSE;
}
