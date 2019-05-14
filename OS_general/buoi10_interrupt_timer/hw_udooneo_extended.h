#ifndef _HW_UDOO_EXNTENDED_H_
#define _HW_UDOO_EXTENDED_H_

#define read_reg(reg, mask)	*((unsigned long *)reg) & (mask)
#define write_reg(reg,value)	*((unsigned long*)reg) = value

#define GPIO_BASE		0x0209C000u
#define GPIO1			0x0000
#define GPIO2			0x1000
#define GPIO3			0x2000
#define GPIO4			0x3000
#define GPIO5			0x4000
#define GPIO6			0x5000
#define GPIO7			0x6000

#define GPIO_DR			0x00u
#define GPIO_GDIR		0x04u
#define GPIP_PSR		0x08u
#define GPIO_ICR1		0x0Cu
#define GPIO_ICR2		0x10u
#define GPIO_IMR		0x14u
#define GPIO_ISR		0x18u
#define GPIO_EDGE_SEL		0x1Cu

#define IOMUXC_BASE		0x020E0000u
#define IOMUXC_GPIO1(x)		(0x14 * ((int)x))	

#define MUX_MODE_MASK		(~(0x0F << 0))

#define ALT0			(0x00 << 0)
#define ALT1			(0x01 << 0)
#define ALT2			(0x02 << 0)
#define ALT3			(0x03 << 0)
#define ALT4			(0x04 << 0)
#define ALT5			(0x05 << 0) 


int gpio_init(unsigned int *gpio,
	unsigned int *iomuxc,
	unsigned char port,
	unsigned char pin, const char* mode);
int gpio_setPin(unsigned int *base,
	unsigned char port,
	unsigned char pin,
	unsigned char value);
char gpio_getPin(unsigned int *gpio, unsigned char port, unsigned char pin);



#endif /* _HW_UDOO_EXTENDED_H_*/
