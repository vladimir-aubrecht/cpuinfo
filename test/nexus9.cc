#include <gtest/gtest.h>

#include <cpuinfo.h>
#include <cpuinfo-mock.h>


TEST(PROCESSORS, count) {
	ASSERT_EQ(2, cpuinfo_processors_count);
}

TEST(PROCESSORS, non_null) {
	ASSERT_TRUE(cpuinfo_processors);
}

TEST(PROCESSORS, smt_id) {
	for (uint32_t i = 0; i < cpuinfo_processors_count; i++) {
		ASSERT_EQ(0, cpuinfo_processors[i].smt_id);
	}
}

TEST(PROCESSORS, core) {
	for (uint32_t i = 0; i < cpuinfo_processors_count; i++) {
		ASSERT_EQ(&cpuinfo_cores[i], cpuinfo_processors[i].core);
	}
}

TEST(PROCESSORS, package) {
	for (uint32_t i = 0; i < cpuinfo_processors_count; i++) {
		ASSERT_EQ(&cpuinfo_packages[0], cpuinfo_processors[i].package);
	}
}

TEST(PROCESSORS, linux_id) {
	for (uint32_t i = 0; i < cpuinfo_processors_count; i++) {
		ASSERT_EQ(i, cpuinfo_processors[i].linux_id);
	}
}

TEST(PROCESSORS, l1i) {
	for (uint32_t i = 0; i < cpuinfo_processors_count; i++) {
		ASSERT_EQ(&cpuinfo_get_l1i_cache().instances[i], cpuinfo_processors[i].cache.l1i);
	}
}

TEST(PROCESSORS, l1d) {
	for (uint32_t i = 0; i < cpuinfo_processors_count; i++) {
		ASSERT_EQ(&cpuinfo_get_l1d_cache().instances[i], cpuinfo_processors[i].cache.l1d);
	}
}

TEST(PROCESSORS, l2) {
	for (uint32_t i = 0; i < cpuinfo_processors_count; i++) {
		ASSERT_EQ(&cpuinfo_get_l2_cache().instances[0], cpuinfo_processors[i].cache.l2);
	}
}

TEST(PROCESSORS, l3) {
	for (uint32_t i = 0; i < cpuinfo_processors_count; i++) {
		ASSERT_FALSE(cpuinfo_processors[i].cache.l3);
	}
}

TEST(PROCESSORS, l4) {
	for (uint32_t i = 0; i < cpuinfo_processors_count; i++) {
		ASSERT_FALSE(cpuinfo_processors[i].cache.l4);
	}
}

TEST(CORES, count) {
	ASSERT_EQ(2, cpuinfo_cores_count);
}

TEST(CORES, non_null) {
	ASSERT_TRUE(cpuinfo_cores);
}

TEST(CORES, processor_start) {
	for (uint32_t i = 0; i < cpuinfo_cores_count; i++) {
		ASSERT_EQ(i, cpuinfo_cores[i].processor_start);
	}
}

TEST(CORES, processor_count) {
	for (uint32_t i = 0; i < cpuinfo_cores_count; i++) {
		ASSERT_EQ(1, cpuinfo_cores[i].processor_count);
	}
}

TEST(CORES, core_id) {
	for (uint32_t i = 0; i < cpuinfo_cores_count; i++) {
		ASSERT_EQ(i, cpuinfo_cores[i].core_id);
	}
}

TEST(CORES, package) {
	for (uint32_t i = 0; i < cpuinfo_cores_count; i++) {
		ASSERT_EQ(&cpuinfo_packages[0], cpuinfo_cores[i].package);
	}
}

TEST(CORES, vendor) {
	for (uint32_t i = 0; i < cpuinfo_cores_count; i++) {
		ASSERT_EQ(cpuinfo_vendor_nvidia, cpuinfo_cores[i].vendor);
	}
}

TEST(CORES, uarch) {
	for (uint32_t i = 0; i < cpuinfo_cores_count; i++) {
		ASSERT_EQ(cpuinfo_uarch_denver, cpuinfo_cores[i].uarch);
	}
}

TEST(CORES, midr) {
	for (uint32_t i = 0; i < cpuinfo_cores_count; i++) {
		ASSERT_EQ(UINT32_C(0x4E0F0000), cpuinfo_cores[i].midr);
	}
}

TEST(PACKAGES, count) {
	ASSERT_EQ(1, cpuinfo_packages_count);
}

TEST(PACKAGES, name) {
	for (uint32_t i = 0; i < cpuinfo_packages_count; i++) {
		ASSERT_EQ("nVidia Tegra T132",
			std::string(cpuinfo_packages[i].name,
				strnlen(cpuinfo_packages[i].name, CPUINFO_PACKAGE_NAME_MAX)));
	}
}

TEST(PACKAGES, processor_start) {
	for (uint32_t i = 0; i < cpuinfo_packages_count; i++) {
		ASSERT_EQ(0, cpuinfo_packages[i].processor_start);
	}
}

TEST(PACKAGES, processor_count) {
	for (uint32_t i = 0; i < cpuinfo_packages_count; i++) {
		ASSERT_EQ(2, cpuinfo_packages[i].processor_count);
	}
}

TEST(PACKAGES, core_start) {
	for (uint32_t i = 0; i < cpuinfo_packages_count; i++) {
		ASSERT_EQ(0, cpuinfo_packages[i].core_start);
	}
}

TEST(PACKAGES, core_count) {
	for (uint32_t i = 0; i < cpuinfo_packages_count; i++) {
		ASSERT_EQ(2, cpuinfo_packages[i].core_count);
	}
}

TEST(ISA, thumb) {
	#if CPUINFO_ARCH_ARM
		ASSERT_TRUE(cpuinfo_has_arm_thumb());
	#elif CPUINFO_ARCH_ARM64
		ASSERT_FALSE(cpuinfo_has_arm_thumb());
	#endif
}

TEST(ISA, thumb2) {
	#if CPUINFO_ARCH_ARM
		ASSERT_TRUE(cpuinfo_has_arm_thumb2());
	#elif CPUINFO_ARCH_ARM64
		ASSERT_FALSE(cpuinfo_has_arm_thumb2());
	#endif
}

TEST(ISA, armv5e) {
	#if CPUINFO_ARCH_ARM
		ASSERT_TRUE(cpuinfo_has_arm_v5e());
	#elif CPUINFO_ARCH_ARM64
		ASSERT_FALSE(cpuinfo_has_arm_v5e());
	#endif
}

TEST(ISA, armv6) {
	#if CPUINFO_ARCH_ARM
		ASSERT_TRUE(cpuinfo_has_arm_v6());
	#elif CPUINFO_ARCH_ARM64
		ASSERT_FALSE(cpuinfo_has_arm_v6());
	#endif
}

TEST(ISA, armv6k) {
	#if CPUINFO_ARCH_ARM
		ASSERT_TRUE(cpuinfo_has_arm_v6k());
	#elif CPUINFO_ARCH_ARM64
		ASSERT_FALSE(cpuinfo_has_arm_v6k());
	#endif
}

TEST(ISA, armv7) {
	#if CPUINFO_ARCH_ARM
		ASSERT_TRUE(cpuinfo_has_arm_v7());
	#elif CPUINFO_ARCH_ARM64
		ASSERT_FALSE(cpuinfo_has_arm_v7());
	#endif
}

TEST(ISA, armv7mp) {
	#if CPUINFO_ARCH_ARM
		ASSERT_TRUE(cpuinfo_has_arm_v7mp());
	#elif CPUINFO_ARCH_ARM64
		ASSERT_FALSE(cpuinfo_has_arm_v7mp());
	#endif
}

TEST(ISA, idiv) {
	ASSERT_TRUE(cpuinfo_has_arm_idiv());
}

TEST(ISA, vfpv2) {
	ASSERT_FALSE(cpuinfo_has_arm_vfpv2());
}

TEST(ISA, vfpv3) {
	ASSERT_TRUE(cpuinfo_has_arm_vfpv3());
}

TEST(ISA, vfpv3_d32) {
	ASSERT_TRUE(cpuinfo_has_arm_vfpv3_d32());
}

TEST(ISA, vfpv3_fp16) {
	ASSERT_TRUE(cpuinfo_has_arm_vfpv3_fp16());
}

TEST(ISA, vfpv3_fp16_d32) {
	ASSERT_TRUE(cpuinfo_has_arm_vfpv3_fp16_d32());
}

TEST(ISA, vfpv4) {
	ASSERT_TRUE(cpuinfo_has_arm_vfpv4());
}

TEST(ISA, vfpv4_d32) {
	ASSERT_TRUE(cpuinfo_has_arm_vfpv4_d32());
}

TEST(ISA, wmmx) {
	ASSERT_FALSE(cpuinfo_has_arm_wmmx());
}

TEST(ISA, wmmx2) {
	ASSERT_FALSE(cpuinfo_has_arm_wmmx2());
}

TEST(ISA, neon) {
	ASSERT_TRUE(cpuinfo_has_arm_neon());
}

TEST(ISA, neon_fp16) {
	ASSERT_TRUE(cpuinfo_has_arm_neon_fp16());
}

TEST(ISA, neon_fma) {
	ASSERT_TRUE(cpuinfo_has_arm_neon_fma());
}

TEST(ISA, atomics) {
	ASSERT_FALSE(cpuinfo_has_arm_atomics());
}

TEST(ISA, neon_rdm) {
	ASSERT_FALSE(cpuinfo_has_arm_neon_rdm());
}

TEST(ISA, fp16_arith) {
	ASSERT_FALSE(cpuinfo_has_arm_fp16_arith());
}

TEST(ISA, jscvt) {
	ASSERT_FALSE(cpuinfo_has_arm_jscvt());
}

TEST(ISA, fcma) {
	ASSERT_FALSE(cpuinfo_has_arm_fcma());
}

TEST(ISA, aes) {
	ASSERT_TRUE(cpuinfo_has_arm_aes());
}

TEST(ISA, sha1) {
	ASSERT_TRUE(cpuinfo_has_arm_sha1());
}

TEST(ISA, sha2) {
	ASSERT_TRUE(cpuinfo_has_arm_sha2());
}

TEST(ISA, pmull) {
	ASSERT_TRUE(cpuinfo_has_arm_pmull());
}

TEST(ISA, crc32) {
	ASSERT_TRUE(cpuinfo_has_arm_crc32());
}

TEST(L1I, count) {
	cpuinfo_caches l1i = cpuinfo_get_l1i_cache();
	ASSERT_EQ(2, l1i.count);
}

TEST(L1I, non_null) {
	cpuinfo_caches l1i = cpuinfo_get_l1i_cache();
	ASSERT_TRUE(l1i.instances);
}

TEST(L1I, size) {
	cpuinfo_caches l1i = cpuinfo_get_l1i_cache();
	for (uint32_t k = 0; k < l1i.count; k++) {
		ASSERT_EQ(128 * 1024, l1i.instances[k].size);
	}
}

TEST(L1I, associativity) {
	cpuinfo_caches l1i = cpuinfo_get_l1i_cache();
	for (uint32_t k = 0; k < l1i.count; k++) {
		ASSERT_EQ(4, l1i.instances[k].associativity);
	}
}

TEST(L1I, sets) {
	cpuinfo_caches l1i = cpuinfo_get_l1i_cache();
	for (uint32_t k = 0; k < l1i.count; k++) {
		ASSERT_EQ(l1i.instances[k].size,
			l1i.instances[k].sets * l1i.instances[k].line_size * l1i.instances[k].partitions * l1i.instances[k].associativity);
	}
}

TEST(L1I, partitions) {
	cpuinfo_caches l1i = cpuinfo_get_l1i_cache();
	for (uint32_t k = 0; k < l1i.count; k++) {
		ASSERT_EQ(1, l1i.instances[k].partitions);
	}
}

TEST(L1I, line_size) {
	cpuinfo_caches l1i = cpuinfo_get_l1i_cache();
	for (uint32_t k = 0; k < l1i.count; k++) {
		ASSERT_EQ(64, l1i.instances[k].line_size);
	}
}

TEST(L1I, flags) {
	cpuinfo_caches l1i = cpuinfo_get_l1i_cache();
	for (uint32_t k = 0; k < l1i.count; k++) {
		ASSERT_EQ(0, l1i.instances[k].flags);
	}
}

TEST(L1I, processors) {
	cpuinfo_caches l1i = cpuinfo_get_l1i_cache();
	for (uint32_t k = 0; k < l1i.count; k++) {
		ASSERT_EQ(k, l1i.instances[k].processor_start);
		ASSERT_EQ(1, l1i.instances[k].processor_count);
	}
}

TEST(L1D, count) {
	cpuinfo_caches l1d = cpuinfo_get_l1d_cache();
	ASSERT_EQ(2, l1d.count);
}

TEST(L1D, non_null) {
	cpuinfo_caches l1d = cpuinfo_get_l1d_cache();
	ASSERT_TRUE(l1d.instances);
}

TEST(L1D, size) {
	cpuinfo_caches l1d = cpuinfo_get_l1d_cache();
	for (uint32_t k = 0; k < l1d.count; k++) {
		ASSERT_EQ(64 * 1024, l1d.instances[k].size);
	}
}

TEST(L1D, associativity) {
	cpuinfo_caches l1d = cpuinfo_get_l1d_cache();
	for (uint32_t k = 0; k < l1d.count; k++) {
		ASSERT_EQ(4, l1d.instances[k].associativity);
	}
}

TEST(L1D, sets) {
	cpuinfo_caches l1d = cpuinfo_get_l1d_cache();
	for (uint32_t k = 0; k < l1d.count; k++) {
		ASSERT_EQ(l1d.instances[k].size,
			l1d.instances[k].sets * l1d.instances[k].line_size * l1d.instances[k].partitions * l1d.instances[k].associativity);
	}
}

TEST(L1D, partitions) {
	cpuinfo_caches l1d = cpuinfo_get_l1d_cache();
	for (uint32_t k = 0; k < l1d.count; k++) {
		ASSERT_EQ(1, l1d.instances[k].partitions);
	}
}

TEST(L1D, line_size) {
	cpuinfo_caches l1d = cpuinfo_get_l1d_cache();
	for (uint32_t k = 0; k < l1d.count; k++) {
		ASSERT_EQ(64, l1d.instances[k].line_size);
	}
}

TEST(L1D, flags) {
	cpuinfo_caches l1d = cpuinfo_get_l1d_cache();
	for (uint32_t k = 0; k < l1d.count; k++) {
		ASSERT_EQ(0, l1d.instances[k].flags);
	}
}

TEST(L1D, processors) {
	cpuinfo_caches l1d = cpuinfo_get_l1d_cache();
	for (uint32_t k = 0; k < l1d.count; k++) {
		ASSERT_EQ(k, l1d.instances[k].processor_start);
		ASSERT_EQ(1, l1d.instances[k].processor_count);
	}
}

TEST(L2, count) {
	cpuinfo_caches l2 = cpuinfo_get_l2_cache();
	ASSERT_EQ(1, l2.count);
}

TEST(L2, non_null) {
	cpuinfo_caches l2 = cpuinfo_get_l2_cache();
	ASSERT_TRUE(l2.instances);
}

TEST(L2, size) {
	cpuinfo_caches l2 = cpuinfo_get_l2_cache();
	for (uint32_t k = 0; k < l2.count; k++) {
		ASSERT_EQ(2 * 1024 * 1024, l2.instances[k].size);
	}
}

TEST(L2, associativity) {
	cpuinfo_caches l2 = cpuinfo_get_l2_cache();
	for (uint32_t k = 0; k < l2.count; k++) {
		ASSERT_EQ(16, l2.instances[k].associativity);
	}
}

TEST(L2, sets) {
	cpuinfo_caches l2 = cpuinfo_get_l2_cache();
	for (uint32_t k = 0; k < l2.count; k++) {
		ASSERT_EQ(l2.instances[k].size,
			l2.instances[k].sets * l2.instances[k].line_size * l2.instances[k].partitions * l2.instances[k].associativity);
	}
}

TEST(L2, partitions) {
	cpuinfo_caches l2 = cpuinfo_get_l2_cache();
	for (uint32_t k = 0; k < l2.count; k++) {
		ASSERT_EQ(1, l2.instances[k].partitions);
	}
}

TEST(L2, line_size) {
	cpuinfo_caches l2 = cpuinfo_get_l2_cache();
	for (uint32_t k = 0; k < l2.count; k++) {
		ASSERT_EQ(64, l2.instances[k].line_size);
	}
}

TEST(L2, flags) {
	cpuinfo_caches l2 = cpuinfo_get_l2_cache();
	for (uint32_t k = 0; k < l2.count; k++) {
		ASSERT_EQ(0, l2.instances[k].flags);
	}
}

TEST(L2, processors) {
	cpuinfo_caches l2 = cpuinfo_get_l2_cache();
	for (uint32_t k = 0; k < l2.count; k++) {
		ASSERT_EQ(0, l2.instances[k].processor_start);
		ASSERT_EQ(2, l2.instances[k].processor_count);
	}
}

TEST(L3, none) {
	cpuinfo_caches l3 = cpuinfo_get_l3_cache();
	ASSERT_EQ(0, l3.count);
	ASSERT_FALSE(l3.instances);
}

TEST(L4, none) {
	cpuinfo_caches l4 = cpuinfo_get_l4_cache();
	ASSERT_EQ(0, l4.count);
	ASSERT_FALSE(l4.instances);
}

#include <nexus9.h>

int main(int argc, char* argv[]) {
	cpuinfo_mock_filesystem(filesystem);
#ifdef __ANDROID__
	cpuinfo_mock_android_properties(properties);
#endif
	cpuinfo_initialize();
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
