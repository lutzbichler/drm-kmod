// SPDX-License-Identifier: MIT
//
// Copyright 2024 Advanced Micro Devices, Inc.

#ifndef __DCN401_CLK_MGR_H_
#define __DCN401_CLK_MGR_H_

void dcn401_init_clocks(struct clk_mgr *clk_mgr_base);

void dcn401_clk_mgr_construct(struct dc_context *ctx,
		struct clk_mgr_internal *clk_mgr,
		struct pp_smu_funcs *pp_smu,
		struct dccg *dccg);

void dcn401_update_clocks_update_dpp_dto(struct clk_mgr_internal *clk_mgr,
		struct dc_state *context, bool safe_to_lower, int dppclk_khz);

void dcn401_clk_mgr_destroy(struct clk_mgr_internal *clk_mgr);



#endif /* __DCN401_CLK_MGR_H_ */