import 'package:flutter/material.dart';
import 'package:supabase_flutter/supabase_flutter.dart';
import 'screens/dashboard_screen.dart';

const String supabaseUrl = 'https://mnyjdwffbiqwiznupecp.supabase.co';
const String supabaseAnonKey =
    'eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Im1ueWpkd2ZmYmlxd2l6bnVwZWNwIiwicm9sZSI6ImFub24iLCJpYXQiOjE3ODIyODE3MDQsImV4cCI6MjA5Nzg1NzcwNH0.ioUkA_sK996QbTqYOcRmir0Pvr_kxnHpHDoh9BwJd20';

Future<void> main() async {
  WidgetsFlutterBinding.ensureInitialized();

  await Supabase.initialize(
    url: supabaseUrl,
    anonKey: supabaseAnonKey,
  );

  runApp(const SmartStreetLightApp());
}

class SmartStreetLightApp extends StatelessWidget {
  const SmartStreetLightApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Smart Street Light',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(
          seedColor: const Color(0xFF1A1F2E),
          brightness: Brightness.dark,
        ),
        useMaterial3: true,
      ),
      home: const DashboardScreen(),
    );
  }
}
