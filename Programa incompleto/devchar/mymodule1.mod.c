#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x5b753d65, "module_layout" },
	{ 0x999e8297, "vfree" },
	{ 0x401917e2, "class_unregister" },
	{ 0x51cb494c, "device_destroy" },
	{ 0x9a76f11f, "__mutex_init" },
	{ 0x4422d30, "class_destroy" },
	{ 0xc347d19e, "device_create" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xf67c881e, "__class_create" },
	{ 0x42e576f6, "__register_chrdev" },
	{ 0xb3b42a38, "mutex_trylock" },
	{ 0xb44ad4b3, "_copy_to_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x6509f33f, "tra" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x7c32d0f0, "printk" },
	{ 0xa6093a32, "mutex_unlock" },
	{ 0xbdfb6dbb, "__fentry__" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=mymodule2";


MODULE_INFO(srcversion, "98A55CC9A8B674620626EC3");
