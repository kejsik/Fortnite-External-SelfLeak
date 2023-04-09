#pragma once
#include <stdint.h>



namespace fptr_data
{
	enum class kernel_opr : uint32_t
	{
		read = 1,
		write,
		get_process_module,
		get_process_base,
	};


	enum class kernel_err : uint16_t
	{
		invalid_process = 2,
		check_fail,
		no_operation,
		invalid_data,

		no_error = 0,
		unset_err = 1
	};

	struct kernel_com
	{
		bool success;
		kernel_err error;

		kernel_opr opr;
		uintptr_t src;
		uintptr_t dst;

		uint32_t target_pid;
		uint32_t user_pid;

		uintptr_t address;
		uintptr_t buffer;

		uintptr_t mdl;

		uintptr_t base;
		char signature[260];
		union
		{
			size_t size;
			const char* name;
		};

		size_t transfer;
	};
}