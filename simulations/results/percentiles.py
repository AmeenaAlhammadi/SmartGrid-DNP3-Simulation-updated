import pandas as pd

heavy = pd.read_csv("HeavyTrafficPacket.csv")     
# choose the column you care about, e.g. the first one:
mean_delay_heavy = heavy.iloc[:,1].mean()
p95_heavy        = heavy.iloc[:,1].quantile(0.95)
p99_heavy        = heavy.iloc[:,1].quantile(0.99)

print("Heavy traffic:")
print("Mean delay:", mean_delay_heavy)
print("P95 delay:", p95_heavy)
print("P99 delay:", p99_heavy)
print("\n")


light = pd.read_csv("LightTrafficPacket.csv")     

# choose the column you care about, e.g. the first one:
mean_delay_light = light.iloc[:,1].mean()
p95_light        = light.iloc[:,1].quantile(0.95)
p99_light        = light.iloc[:,1].quantile(0.99)

print("Light traffic:")
print("Mean delay:", mean_delay_light)
print("P95 delay:", p95_light)
print("P99 delay:", p99_light)