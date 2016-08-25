/*
 * Centaurean Density
 *
 * Copyright (c) 2013, Guillaume Voirin
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     1. Redistributions of source code must retain the above copyright notice, this
 *        list of conditions and the following disclaimer.
 *
 *     2. Redistributions in binary form must reproduce the above copyright notice,
 *        this list of conditions and the following disclaimer in the documentation
 *        and/or other materials provided with the distribution.
 *
 *     3. Neither the name of the copyright holder nor the names of its
 *        contributors may be used to endorse or promote products derived from
 *        this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * 18/10/13 22:30
 */

#include "main_footer.h"

DENSITY_WINDOWS_EXPORT DENSITY_FORCE_INLINE uint_fast32_t density_main_footer_read(density_memory_location *restrict in, density_main_footer *restrict footer) {
    DENSITY_MEMCPY(&footer->previousBlockRelativeStartPosition, in->pointer, sizeof(density_main_footer));
    in->pointer += sizeof(density_main_footer);
    in->available_bytes -= sizeof(density_main_footer);

    return sizeof(density_main_footer);
}

DENSITY_WINDOWS_EXPORT DENSITY_FORCE_INLINE uint_fast32_t density_main_footer_write(density_memory_location *out, const uint32_t relativePosition) {
    DENSITY_MEMCPY(out->pointer, &relativePosition, sizeof(density_main_footer));
    out->pointer += sizeof(density_main_footer);
    out->available_bytes -= sizeof(density_main_footer);

    return sizeof(density_main_footer);
}