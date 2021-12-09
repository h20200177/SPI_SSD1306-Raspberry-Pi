# SPI_SSD1306-Raspberry-Pi

## SPI Protocol Driver in Linux Kernel
Steps that involve writing the SPI protocol device driver are given below.
Get the SPI Controller driver
Add the slave device to the SPI Controller
Configure the SPI
Now the driver is ready. So you can transfer the data between master and slave.
Once you are done, then remove the device.
Get the SPI Controller driver
First, we need to get the controller driver. To do that, we can use the below API. Before using that API, we need to know which SPI bus we are using.
struct spi_controller * spi_busnum_to_master(u16 bus_num)
It returns a pointer to the relevant spi_controller (which the caller must release), or NULL if there is no such master registered.
 
Add the slave device to the SPI Controller
In this step, you need to create a spi_board_info structure that has the slave device’s details.
Once we have filled the above structure, then we can use the below API to add the slave device to the SPI controller driver.
struct spi_device * spi_new_device( struct spi_controller *ctlr, struct spi_board_info *chip )
It returns the new device, or NULL.
 
 
Configure the SPI
Till now, we have added the slave device to the controller driver. If we change any mode or clock frequency, then we have to call this below API to take effect on the bus.
 
int spi_setup(struct spi_device *spi)
Return
It returns zero on success, else a negative error code.
 
Message Transfer
We have done our initialization. Now we can transfer the data using the below APIs.
This function will be blocked until the master completes the transfer.
int spi_sync_transfer(struct spi_device *spi, struct spi_transfer *xfers, unsigned int num_xfers)
It returns zero on success, else a negative error code.
This API is used to transfer the data asynchronously. This call may be used in_irq and other contexts which can’t sleep,
int spi_async(struct spi_device *spi, struct spi_message *message)
It returns zero on success, else a negative error code.
This API is used to write the data and followed by a read. This is synchronous.
int spi_write_then_read(struct spi_device * spi, const void * txbuf, unsigned n_tx, void * rxbuf, unsigned n_rx)
 
Remove the device
Using the below API, you can unregister the slave device.
void spi_unregister_device(struct spi_device *spi)
## Loading and Unloading Modules
After the module is built, the next step is loading it into the kernel. As we’ve already pointed out, insmod does the job for you. The program loads the module code and data into the kernel, which, in turn, performs a function similar to that of ld, in that it links any unresolved symbol in the module to the symbol table of the kernel. Unlike the linker, however, the kernel doesn’t modify the module’s disk file, but rather an in-memory copy. insmod accepts a number of command-line options (for details, see the manpage), and it can assign values to parameters in your module before linking it to the current kernel. Thus, if a module is correctly designed, it can be configured at load time; load-time configuration gives the user more flexibility than compile-time configuration.
## Device drivers in user space
 
Traditionally, packet-processing or data-path applications in Linux have run in the kernel space due to the infrastructure provided by the Linux network stack. Frameworks such as netdevice drivers and netfilters have provided means for applications to directly hook into the packet-processing path within the kernel.
However, a shift toward running data-path applications in the user-space context is now occurring. The Linux user space provides several advantages for applications, including more robust and flexible process management, standardized system-call interface, simpler resource management, a large number of libraries for XML, and regular expression parsing, among others. It also makes applications more straightforward to debug by providing memory isolation and independent restart. At the same time, while kernel-space applications need to conform to General Public License guidelines, user-space applications are not bound by such restrictions.
User-space data-path processing comes with its own overheads. Since the network drivers run in kernel context and use kernel-space memory for packet storage, there is an overhead of copying the packet data from user-space to kernel-space memory and vice versa. Also, user/kernel-mode transitions usually impose a considerable performance overhead, thereby violating the low-latency and high-throughput requirements of data-path applications.
