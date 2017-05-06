library(dplyr)

runs <- dir(pattern="run.*log")

names(runs) <- gsub("\\.log", "", gsub("run_", "", runs))
runs

dat <- sapply(runs, function(r) as.numeric(gsub(".*\\(([0-9]+)( ms.*)", "\\1", grep("ms\\)", readLines(r), value=TRUE))))

dat <- as.data.frame(dat)

dat[c("algo", "case")] <- list(c("bdf", "bdf", "rk45", "rk45"), c("ref", "checked", "ref", "checked"))

dat


library(tidyr)

ldat <- gather(dat, run, time, -algo, -case)

ldat <- ldat %>% separate(run, c("repl", "cpu", "scpu")) %>% mutate(time=time /1e3, scpun=as.numeric(scpu))


library(ggplot2)
theme_set(theme_bw())

ldat

ggplot(ldat, aes(scpu, time, colour=case, shape=case)) + facet_grid(algo~., scale="free_y") + geom_jitter() +
    scale_y_log10(breaks=c(1:10, seq(10, 100, by=10))) + ylab("Time [s]") + xlab("Concurrent CPUs used (4-core laptop with hyperthreading)")

ggsave("perf_checking_hornberg.pdf", width=6, height=7)

ggplot(subset(ldat, algo=="rk45"), aes(case, time, colour=case, shape=case)) + facet_grid(scpu~., scale="free_y") + geom_jitter() +
    scale_y_log10(breaks=c(1:10, seq(10, 100, by=10))) + ylab("Time [s]") + xlab("Concurrent CPUs used (4-core laptop with hyperthreading)") + ggtitle("RK45 only by case")


lf <- lapply(c(1,4,8,12,24), function(mc) lm(log(time) ~ case, subset(ldat, algo=="rk45" & scpun==mc)))

names(lf) <- c(1,4,8,12,24)

library(broom)

res <- sapply(lf, function(l) tidy(l)[2,-1])
print(as.data.frame(res), digits=3)

lf2 <- lapply(c(1,4,8,12,24), function(mc) lm(log(time/scpun) ~ case, subset(ldat, algo=="rk45" & scpun==mc)))

res2 <- sapply(lf2, function(l) tidy(l)[2,-1])
print(as.data.frame(res2), digits=3)



write.csv(ldat, "perf_checking_hornberg.csv")

