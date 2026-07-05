import 'dart:async';
import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import '../models/street_light_log.dart';
import '../services/street_light_service.dart';
import '../widgets/led_indicator.dart';
import '../widgets/intensity_gauge.dart';
import '../widgets/history_tile.dart';

class DashboardScreen extends StatefulWidget {
  const DashboardScreen({super.key});

  @override
  State<DashboardScreen> createState() => _DashboardScreenState();
}

class _DashboardScreenState extends State<DashboardScreen> {
  final StreetLightService _service = StreetLightService();

  StreetLightLog? _latest;
  List<StreetLightLog> _history = [];
  bool _loading = true;
  bool _refreshing = false;
  String? _error;

  // Auto-refresh every 7 s (matches ESP32 send interval)
  Timer? _autoRefreshTimer;
  static const _autoRefreshInterval = Duration(seconds: 7);

  @override
  void initState() {
    super.initState();
    _loadData();
    _autoRefreshTimer =
        Timer.periodic(_autoRefreshInterval, (_) => _loadData(silent: true));
  }

  @override
  void dispose() {
    _autoRefreshTimer?.cancel();
    super.dispose();
  }

  Future<void> _loadData({bool silent = false}) async {
    if (!silent) {
      setState(() {
        _loading = _latest == null;
        _refreshing = _latest != null;
        _error = null;
      });
    }

    try {
      final results = await Future.wait([
        _service.fetchLatest(),
        _service.fetchHistory(limit: 10),
      ]);

      if (!mounted) return;
      setState(() {
        _latest = results[0] as StreetLightLog?;
        _history = results[1] as List<StreetLightLog>;
        _loading = false;
        _refreshing = false;
        _error = null;
      });
    } catch (e) {
      if (!mounted) return;
      setState(() {
        _loading = false;
        _refreshing = false;
        _error = e.toString().replaceFirst('Exception: ', '');
      });
    }
  }

  Color get _accentColor {
    if (_latest == null) return const Color(0xFF78909C);
    switch (_latest!.ledColor) {
      case LedColor.green:
        return const Color(0xFF00E676);
      case LedColor.blue:
        return const Color(0xFF40C4FF);
      case LedColor.red:
      case LedColor.redBlink:
        return const Color(0xFFFF1744);
      case LedColor.unknown:
        return const Color(0xFF78909C);
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: const Color(0xFF0D1117),
      body: SafeArea(
        child: _loading
            ? const Center(
                child: Column(
                  mainAxisAlignment: MainAxisAlignment.center,
                  children: [
                    CircularProgressIndicator(
                        color: Color(0xFF40C4FF), strokeWidth: 2),
                    SizedBox(height: 16),
                    Text('Connecting to Supabase…',
                        style:
                            TextStyle(color: Colors.white54, fontSize: 13)),
                  ],
                ),
              )
            : RefreshIndicator(
                onRefresh: _loadData,
                color: _accentColor,
                backgroundColor: const Color(0xFF1A1F2E),
                child: CustomScrollView(
                  slivers: [
                    SliverToBoxAdapter(child: _buildHeader()),
                    if (_error != null)
                      SliverToBoxAdapter(child: _buildError()),
                    if (_latest != null) ...[
                      SliverToBoxAdapter(child: _buildStatusCard()),
                      SliverToBoxAdapter(child: _buildGaugeAndLed()),
                      SliverToBoxAdapter(child: _buildTimestamp()),
                      SliverToBoxAdapter(child: _buildHistoryHeader()),
                    ],
                    if (_history.isNotEmpty)
                      SliverPadding(
                        padding: const EdgeInsets.symmetric(horizontal: 20),
                        sliver: SliverList(
                          delegate: SliverChildBuilderDelegate(
                            (ctx, i) => HistoryTile(
                              log: _history[i],
                              isLatest: i == 0,
                            ),
                            childCount: _history.length,
                          ),
                        ),
                      ),
                    const SliverToBoxAdapter(
                        child: SizedBox(height: 32)),
                  ],
                ),
              ),
      ),
    );
  }

  Widget _buildHeader() {
    return Padding(
      padding: const EdgeInsets.fromLTRB(20, 20, 20, 8),
      child: Row(
        children: [
          // Icon
          Container(
            width: 40,
            height: 40,
            decoration: BoxDecoration(
              color: _accentColor.withOpacity(0.12),
              borderRadius: BorderRadius.circular(10),
              border: Border.all(color: _accentColor.withOpacity(0.3)),
            ),
            child: Icon(Icons.lightbulb_outline,
                color: _accentColor, size: 22),
          ),
          const SizedBox(width: 12),
          const Expanded(
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(
                  'Smart Street Light',
                  style: TextStyle(
                    color: Colors.white,
                    fontSize: 18,
                    fontWeight: FontWeight.w700,
                    letterSpacing: 0.3,
                  ),
                ),
                Text(
                  'Real-Time Monitor',
                  style: TextStyle(
                    color: Colors.white38,
                    fontSize: 12,
                    letterSpacing: 0.5,
                  ),
                ),
              ],
            ),
          ),
          // Refresh button
          AnimatedRotation(
            turns: _refreshing ? 1 : 0,
            duration: const Duration(milliseconds: 600),
            child: IconButton(
              onPressed: _refreshing ? null : _loadData,
              icon: Icon(
                Icons.refresh_rounded,
                color: _refreshing ? Colors.white24 : Colors.white60,
              ),
              tooltip: 'Refresh now',
            ),
          ),
        ],
      ),
    );
  }

  Widget _buildError() {
    return Container(
      margin: const EdgeInsets.symmetric(horizontal: 20, vertical: 8),
      padding: const EdgeInsets.all(14),
      decoration: BoxDecoration(
        color: const Color(0xFFFF1744).withOpacity(0.08),
        borderRadius: BorderRadius.circular(12),
        border: Border.all(
            color: const Color(0xFFFF1744).withOpacity(0.25)),
      ),
      child: Row(
        children: [
          const Icon(Icons.error_outline,
              color: Color(0xFFFF1744), size: 18),
          const SizedBox(width: 10),
          Expanded(
            child: Text(
              _error!,
              style: const TextStyle(
                  color: Color(0xFFFF8A80), fontSize: 12),
            ),
          ),
        ],
      ),
    );
  }

  Widget _buildStatusCard() {
    final isOn = _latest!.status.toUpperCase() == 'ON';
    return AnimatedContainer(
      duration: const Duration(milliseconds: 400),
      margin: const EdgeInsets.symmetric(horizontal: 20, vertical: 8),
      padding: const EdgeInsets.symmetric(horizontal: 20, vertical: 18),
      decoration: BoxDecoration(
        gradient: LinearGradient(
          colors: [
            _accentColor.withOpacity(0.15),
            _accentColor.withOpacity(0.04),
          ],
          begin: Alignment.topLeft,
          end: Alignment.bottomRight,
        ),
        borderRadius: BorderRadius.circular(18),
        border: Border.all(color: _accentColor.withOpacity(0.25)),
      ),
      child: Row(
        children: [
          Expanded(
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(
                  'STREET LIGHT STATUS',
                  style: TextStyle(
                    color: Colors.white.withOpacity(0.4),
                    fontSize: 10,
                    letterSpacing: 1.8,
                    fontWeight: FontWeight.w600,
                  ),
                ),
                const SizedBox(height: 6),
                Text(
                  isOn ? 'ON' : 'OFF',
                  style: TextStyle(
                    color: Colors.white,
                    fontSize: 32,
                    fontWeight: FontWeight.w800,
                    letterSpacing: 2,
                  ),
                ),
                const SizedBox(height: 4),
                Text(
                  _latest!.conditionLabel,
                  style: TextStyle(
                    color: _accentColor.withOpacity(0.85),
                    fontSize: 12,
                    fontWeight: FontWeight.w500,
                  ),
                ),
              ],
            ),
          ),
          Container(
            width: 56,
            height: 56,
            decoration: BoxDecoration(
              shape: BoxShape.circle,
              color: (isOn ? Colors.amber : Colors.white)
                  .withOpacity(isOn ? 0.12 : 0.06),
              border: Border.all(
                color: (isOn ? Colors.amber : Colors.white38),
                width: 1.5,
              ),
            ),
            child: Icon(
              isOn ? Icons.wb_sunny_rounded : Icons.bedtime_outlined,
              color: isOn ? Colors.amber : Colors.white38,
              size: 26,
            ),
          ),
        ],
      ),
    );
  }

  Widget _buildGaugeAndLed() {
    return Container(
      margin: const EdgeInsets.symmetric(horizontal: 20, vertical: 8),
      padding: const EdgeInsets.all(24),
      decoration: BoxDecoration(
        color: Colors.white.withOpacity(0.03),
        borderRadius: BorderRadius.circular(18),
        border:
            Border.all(color: Colors.white.withOpacity(0.07)),
      ),
      child: Row(
        mainAxisAlignment: MainAxisAlignment.spaceEvenly,
        children: [
          IntensityGauge(intensity: _latest!.intensity),
          Container(
              width: 1,
              height: 100,
              color: Colors.white.withOpacity(0.08)),
          LedIndicator(
            ledColor: _latest!.ledColor,
            size: 80,
          ),
        ],
      ),
    );
  }

  Widget _buildTimestamp() {
    final formatted =
        DateFormat('EEEE, d MMM yyyy  •  HH:mm:ss')
            .format(_latest!.createdAt);
    return Padding(
      padding: const EdgeInsets.symmetric(horizontal: 20, vertical: 4),
      child: Row(
        children: [
          Icon(Icons.access_time_rounded,
              size: 13, color: Colors.white.withOpacity(0.3)),
          const SizedBox(width: 6),
          Text(
            'Last update: $formatted',
            style: TextStyle(
              color: Colors.white.withOpacity(0.35),
              fontSize: 11,
            ),
          ),
          const Spacer(),
          if (_refreshing)
            const SizedBox(
              width: 10,
              height: 10,
              child: CircularProgressIndicator(
                  strokeWidth: 1.5, color: Colors.white30),
            ),
        ],
      ),
    );
  }

  Widget _buildHistoryHeader() {
    return Padding(
      padding: const EdgeInsets.fromLTRB(20, 20, 20, 10),
      child: Row(
        children: [
          const Text(
            'Recent Logs',
            style: TextStyle(
              color: Colors.white,
              fontSize: 16,
              fontWeight: FontWeight.w700,
            ),
          ),
          const Spacer(),
          Text(
            'Auto-refresh every 7s',
            style: TextStyle(
              color: Colors.white.withOpacity(0.3),
              fontSize: 11,
            ),
          ),
        ],
      ),
    );
  }
}
