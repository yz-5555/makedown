const std = @import("std");
const zcc = @import("compile_commands");

pub fn build(b: *std.Build) void {
    const target = b.standardTargetOptions(.{});
    const optimize = b.standardOptimizeOption(.{});
    var zcc_targets = std.ArrayListUnmanaged(*std.Build.Step.Compile){};

    const flags = [_][]const u8{
        "-std=c99",
        // "-std=c++11",
        "-Wall",
        "-Wextra",
        "-Wpedantic",
        "-Wno-deprecated-declarations",
        "-Wstrict-prototypes",
    };

    const exe = b.addExecutable(.{ .name = b.path("foo"), .root_module = b.createModule(.{ .target = target, .optimize = optimize }) }); // Change "foo" to the project name.
    exe.addCSourceFile(.{ .file = "./src/main.c", .flags = &flags });
    // const src = [_][]const u8{
    //     "./src/main.c",
    // };
    // exe.addCSourceFiles(.{ .files = &src, .flags = &flags });
    exe.addIncludePath(b.path("./include"));
    exe.linkLibC();
    // exe.linkLibCpp();
    b.installArtifact(exe);

    zcc_targets.append(b.allocator, exe) catch @panic("OOM");

    const run_cmd = b.addRunArtifact(exe);
    run_cmd.step.dependOn(b.getInstallStep());

    const run_step = b.step("run", "Running the project");
    run_step.dependOn(&run_cmd.step);
    
    _ = zcc.createStep(b, "cdb", zcc_targets.toOwnedSlice(b.allocator) catch @panic("OOM"));
}
