# Slice 6 offer rollover

Each fetch and activation/abandon reconciles persisted kind1/2 offers against the
current UTC day and UTC epoch-aligned seven-day week. Save occurs only when the
roster/dates change. Active/claimable progress, activation and rewards survive;
carried offers use today's offerDay. Previous-period non-active available rows
expire, never appear available with stale dates. Current available rows are
retained (including abandon), then rotated definitions fill three total slots.
Abandon resets progress/usage and uses today's date. Weekly dates also use today;
expirationTimestamp and NextPeriodStartTimes use the actual next week boundary,
not offerDay+7. Kind4 contract policy remains unchanged.

To meet the requested invariant of three live slots with only three local weekly
definitions, exhausted completed definitions are reoffered after unused ones.
This is local replenishment policy, not a claim about retail repeat limits. Old
claim receipt identity survives until activation; reactivation clears it, so an
old ClientTx cannot grant a new instance. Active/claimable count toward slots.
A malformed preexisting roster with more than three active orders is preserved
rather than silently abandoning earned progress; no additional offers are added.

Tests: deterministic day/week rollover, retained progress, daily/weekly
independence, no repeat-fetch regeneration, replenishment and no stale offerDay;
real router accepts3/abandons1/fetches3; NextPeriodStartTimes exact boundaries.
Release and rebuilt harness/run pass in hq-slice6-stage3-*.log. No game launched.
Archived run-51584 proves the prior stale available rows from day20708 alongside
active day20709 rows. The code no longer merges a stateless three-entry list with
stale saved rows to decide what is shown.
